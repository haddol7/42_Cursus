from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.parsers import JSONParser, MultiPartParser
from rest_framework.request import Request
from rest_framework import status
import requests

from django.core.files.uploadedfile import UploadedFile
from django.utils.dateparse import parse_datetime
from django.db.models import Avg, Q
from user.models import Profile, Friend, MatchHistory, UserStats 
from user.serializers import ProfileSerializer, FriendSerializer 
from user.envs import JWT_URL

from PIL import Image
import os


class JWTAuthenticationMixin:
    def check_jwt(self, req: Request):
        if "Authorization" not in req._request.headers:
            raise PermissionError("error: Authorization header is missing.")

        authorization_header: str = req._request.headers["Authorization"]
        if not authorization_header.startswith("Bearer "):
            raise PermissionError("error: Invalid Authorization header.")

        jwt = authorization_header[7:] 
        res = requests.post(
            f"{JWT_URL}/jwt/check", json={"jwt": jwt, "skip_2fa": True}
        )
        if not res.ok:
            error_message = f"JWT_Error: {res.content.decode()} (Status Code: {res.status_code})"
            raise PermissionError(error_message)
        res = res.json()
        return int(res["user_id"]) 
    


# /user
class ProfileDetail(APIView, JWTAuthenticationMixin):
    parser_classes = [JSONParser, MultiPartParser]

    def get(self, req: Request):
        try:
            user_id = self.check_jwt(req)
            user_name: str = req.query_params.get('user_name')
            if user_name:
                user_profile = Profile.objects.filter(user_name=user_name).first()
                if not user_profile:
                    return Response({"error": f"{user_name} is not found."}, status=status.HTTP_404_NOT_FOUND)
            else:
                user_profile = Profile.objects.filter(user_id=user_id).first() # 쿼리가 없는 경우, 본인 프로필 반환
                if not user_profile:
                    return Response({"error": "profile is not found."}, status=status.HTTP_404_NOT_FOUND)

            serializer = ProfileSerializer(user_profile)
            return Response(serializer.data)
        except PermissionError as e:
            return Response({"error": str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': f'Internal Server Error. : {e}'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

    def put(self, req: Request):
        try:
            user_id = self.check_jwt(req)
            user_profile = Profile.objects.filter(user_id=user_id).first()
            if not user_profile:
                return Response({'error': 'user_profile is not found.'}, status=status.HTTP_404_NOT_FOUND)

            image = req.FILES.get('image_url')
            if image:
                if not self.validated_image(image):
                    return Response({'error': 'Invalid image file.'}, status=status.HTTP_400_BAD_REQUEST)
                user_profile.image_url = image
                user_profile.save()

            req_data = req.data.copy()
            req_data.pop('image_url', None) # image_url은 serializer에서 제외 
            
            serializer = ProfileSerializer(user_profile, data=req_data, partial=True)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data)
            else:
                print(serializer.errors)
                return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': f'Internal Server Error. : {e}'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
    
    def validated_image(self, image : UploadedFile) -> bool:
        try:
            valid_extensions = ['.jpg', '.jpeg', '.png', '.gif']

            ext = os.path.splitext(image.name)[1].lower()
            if ext not in valid_extensions:
                print(f"Invalid file extension: {ext}")
                return False

            with Image.open(image) as im:
                im.load()
                if im.format not in ['JPEG', 'PNG', 'GIF']:
                    print(f"Invalid image format: {im.format}")
                    return False
            return True
        except Exception as e:
            print("Invalid image:", e)
            return False
    

# /user/friend
class FriendView(APIView, JWTAuthenticationMixin):
    parser_classes = [JSONParser]

    def get(self, req: Request):
        try:
            user_id = self.check_jwt(req)
            user_profile = Profile.objects.filter(user_id=user_id).first()
            if not user_profile:
                return Response({'error': 'user_profile is not found.'}, status=status.HTTP_404_NOT_FOUND)
            friends = Friend.objects.filter(_user=user_profile)
            serializer = FriendSerializer(friends, many=True)
            return Response(serializer.data, status=status.HTTP_200_OK)
        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': f'Internal Server Error. : {e}'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
        

    def post(self, req: Request):
        try:
            user_id = self.check_jwt(req)
            user_profile = Profile.objects.filter(user_id=user_id).first()
            if not user_profile:
                return Response({'error': 'user_profile is not found.'}, status=status.HTTP_404_NOT_FOUND)
            friend_name = req.data.get('user_name')
            if not friend_name:
                return Response({'error': 'user_name field is required.'}, status=status.HTTP_400_BAD_REQUEST)

            friend_profile = Profile.objects.filter(user_name=friend_name).first()
            if not friend_profile:
                return Response({'error': f'{friend_name} is not found.'}, status=status.HTTP_404_NOT_FOUND)

            if user_profile.user_id == friend_profile.user_id:
                return Response({'error': 'You cannot add yourself as a friend.'}, status=status.HTTP_400_BAD_REQUEST)

            if Friend.objects.filter(_user=user_profile, friend=friend_profile).exists():
                return Response({'error': f'{friend_name} is already your friend.'}, status=status.HTTP_400_BAD_REQUEST)

            Friend.objects.create(_user=user_profile, friend=friend_profile)
            return Response({'message': f'{friend_name} is successfully added as your friend.'}, status=status.HTTP_201_CREATED)

        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': f'Internal Server Error. : {e}'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)



# /user/dashboard
class DashboardView(APIView, JWTAuthenticationMixin):
    parser_classes = [JSONParser]

    def get(self, req: Request):
        try:
            user_id = self.check_jwt(req)
            user_profile = self._get_user_profile(user_id)
            user_stats = self._get_user_stats(user_profile)
            
            current_user_win_rate_trend = self._compute_win_rate_trend(user_profile)
            top_user_stats = self._get_top_user_stats()
            if top_user_stats:
                top_user_win_rate_trend = self._compute_win_rate_trend(top_user_stats.user)
            else:
                top_user_win_rate_trend = [0, 0, 0, 0, 0]
            
            user_total_time = user_stats.total_play_time
            overall_avg_time = self._calculate_game_time()
            recent_user_matches = self._get_recent_user_matches(user_profile)
            top_5_winners = self._get_top_5_winners()
            top_5_game_time = self._get_top_5_game_time()
            recent_matches = self._get_recent_matches()
            
            response_data = {
                "user_session": {
                    "user_stats": {
                        "user_name": user_profile.user_name,
                        "total_games": user_stats.total_games
                    },
                    "user_win_rate": {
                        "wins": user_stats.win_cnt,
                        "losses": user_stats.lose_cnt
                    },
                    "win_rate_trend": {
                        "current_user": current_user_win_rate_trend,
                        "top_user": top_user_win_rate_trend
                    },
                    "total_game_time": {
                        "user_total_time": user_total_time,
                        "avg_total_time": round(overall_avg_time, 1)
                    },
                    "recent_user_matches": recent_user_matches
                },
                "game_session": {
                    "top_5_winners": top_5_winners,
                    "top_5_game_time": top_5_game_time,
                    "recent_matches": recent_matches
                }
            }
            
            return Response(response_data, status=status.HTTP_200_OK)
        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': f'Internal Server Error : {e}'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

    def _get_user_profile(self, user_id: int) -> Profile:
        user_profile = Profile.objects.filter(user_id=user_id).first()
        if not user_profile:
            raise Exception("User profile not found.")
        return user_profile

    def _get_user_stats(self, user_profile: Profile) -> UserStats:
        user_stats = UserStats.objects.filter(user=user_profile).first()
        if not user_stats:
            user_stats = UserStats(
                user=user_profile,
                total_games=0,
                win_cnt=0,
                lose_cnt=0,
                total_play_time=0
			)
        return user_stats

    def _compute_win_rate_trend(self, user: Profile) -> list:
        """
        유저가 참여한 경기들의 누적 승률을 계산하고, 
        마지막 5경기의 승률 추세를 반환
        """
        matches = MatchHistory.objects.filter(
            Q(player1_id=user) | Q(player2_id=user)
        ).order_by('match_date')

        cumulative_wins = 0 #누적된 이긴 횟수
        trend = []
        for idx, match in enumerate(matches, start=1):
            if match.winner_id == user:
                cumulative_wins += 1
            win_rate = cumulative_wins / idx
            trend.append(round(win_rate, 2))
        
        while len(trend) < 5:
            trend.insert(0, 0)
        if len(trend) > 5:
            trend = trend[-5:]
        return trend

    def _get_top_user_stats(self) -> UserStats:
        """
        승리 횟수 기준 1등 유저의 UserStats를 반환
        """
        return UserStats.objects.order_by('-win_cnt').first()

    def _calculate_game_time(self) -> float:
        """
        유저의 전체 평균 게임 시간을 계산 (초 단위)
        """
        overall_avg_play_time = (
            MatchHistory.objects.aggregate(avg_time=Avg('play_time'))['avg_time'] or 0.0
        )
        return overall_avg_play_time

    def _get_recent_user_matches(self, user: Profile) -> list:
        """
        유저가 참여한 최근 10경기의 정보를 반환
        """
        qs = MatchHistory.objects.filter(
            Q(player1_id=user) | Q(player2_id=user)
        ).order_by('-match_date')[:10]
        
        matches = []
        for match in qs:
            if match.player1_id == user:
                opponent = match.player2_id
                user_score = match.player1_score
                opponent_score = match.player2_score
            else:
                opponent = match.player1_id
                user_score = match.player2_score
                opponent_score = match.player1_score

            matches.append({
                "user_name": user.user_name,
                "opponent_name": opponent.user_name,
                "win": (match.winner_id == user),
                "user_score": user_score,
                "opponent_score": opponent_score,
                "game_time": match.play_time,
            })
        if not matches:
            default_match = {
                "user_name": user.user_name,
                "opponent_name": "Nan",
                "win": False,
                "user_score": 0,
                "opponent_score": 0,
                "game_time": 0
			}
            return [default_match]
        return matches

    def _get_top_5_winners(self) -> list:
        """
        상위 5명의 유저네임과 승리 횟수 반환
        """
        qs = UserStats.objects.filter(total_games__gt=0).order_by('-win_cnt')[:5]
        top_winners = [{
            "user_name": stat.user.user_name,
            "win_count": stat.win_cnt
        } for stat in qs]

        while len(top_winners) < 5:
            top_winners.append({"user_name": "Nan", "win_count": 0})

        return top_winners

    def _get_top_5_game_time(self) -> list:
        """
        상위 5명의 유저네임과 총 게임 이용 시간 반환 
        """
        qs = UserStats.objects.filter(total_games__gt=0).order_by('-win_cnt')[:5]
        top_game_time = [{
            "user_name": stat.user.user_name,
            "game_time": stat.total_play_time
        } for stat in qs]

        while len(top_game_time) < 5:
            top_game_time.append({"user_name": "Nan", "game_time": 0})

        return top_game_time

    def _get_recent_matches(self) -> list:
        """
        전체 경기 중 최근 10경기의 정보를 반환
        """
        qs = MatchHistory.objects.all().order_by('-match_date')[:10]
        
        matches = []
        for match in qs:
            if match.winner_id == match.player1_id:
                winner_score = match.player1_score
                loser_score = match.player2_score
                loser_name = match.player2_id.user_name
            else:
                winner_score = match.player2_score
                loser_score = match.player1_score
                loser_name = match.player1_id.user_name

            matches.append({
                "winner_name": match.winner_id.user_name,
                "loser_name": loser_name,
                "winner_score": winner_score,
                "loser_score": loser_score,
                "match_playtime": match.play_time,
            })
        if not matches:
            default_match = {
                "winner_name": "Nan",
                "loser_name": "Nan",
                "winner_score": 0,
                "loser_score": 0,
                "match_playtime": 0
			}
            return [default_match]
        return matches


#/_internal/user
class InternalUserView(APIView):
    parser_classes = [JSONParser]

    def get(self, req: Request):
        try:
            user_id : int = req.query_params.get('user_id')
            if not user_id:
                return Response({'error':'user_id is required.'}, status=status.HTTP_400_BAD_REQUEST)

            profile = Profile.objects.filter(user_id=user_id).first()
            if not profile:
                return Response({'error':'user_id is not found.'}, status=status.HTTP_404_NOT_FOUND)

            user_name : str = profile.user_name
            return Response(user_name, status=status.HTTP_200_OK)
        except Exception as e:
            return Response({'error': f'Internal Server Error. : {e}'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

    def post(self, req: Request):
        try:
            user_id = req.data.get('user_id')
            if not user_id:
                return Response({'error':'user_id is required.'}, status=status.HTTP_400_BAD_REQUEST)
            user_name = req.data.get('user_name')
            if not user_name:
                return Response({'error':'user_name is required.'}, status=status.HTTP_400_BAD_REQUEST)

            profile = Profile.objects.create(user_id=user_id, user_name=user_name)
            profile.save()
            serializer = ProfileSerializer(profile)
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        except Exception as e:
            return Response({'error': f'Internal Server Error. : {e}'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)



#/_internal/dashboard
class InternalDashboardView(APIView):
    parser_classes = [JSONParser]

    def post(self, req :Request):
        try:
            data = req.data
            player1_id = int(data.get("player1_id"))
            player2_id = int(data.get("player2_id"))
            player1_score = int(data.get("player1_score"))
            player2_score = int(data.get("player2_score"))
            winner_id = int(data.get("winner_id"))
            match_date = parse_datetime(data.get("match_date"))
            play_time = int(data.get("play_time"))

            if any(field is None for field in [player1_id, player2_id, player1_score, player2_score, winner_id, match_date, play_time]):
                return Response({"error": "All fields are required."}, status=status.HTTP_400_BAD_REQUEST)

            player1 = Profile.objects.get(pk=player1_id)
            player2 = Profile.objects.get(pk=player2_id)
            winner = Profile.objects.get(pk=winner_id)
            
            match = MatchHistory.objects.create(
                player1_id=player1,
                player2_id=player2,
                player1_score=player1_score,
                player2_score=player2_score,
                winner_id=winner,
                match_date=match_date,
                play_time=play_time
            )
            match.save()
            self.update_user_info(player1_id, winner_id, play_time)
            self.update_user_info(player2_id, winner_id, play_time)
            return Response({"message": "Match recorded successfully."}, status=status.HTTP_201_CREATED)

        except Exception as e:
            return Response({'error': f'Internal Server Error -> {e}'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

    def update_user_info(self, user_id, winner_id, play_time):
        # user profile
        user_profile = Profile.objects.filter(user_id=user_id).first()
        if not user_profile:
            return

        user_profile.total_cnt += 1
        if user_id == winner_id:
            user_profile.win_cnt += 1
        else:
            user_profile.lose_cnt += 1
        user_profile.save()

        # user stat
        user_stats, created = UserStats.objects.get_or_create(user=user_profile)
        user_stats.total_games += 1
        if user_id == winner_id:
            user_stats.win_cnt += 1
        else:
            user_stats.lose_cnt += 1
        user_stats.total_play_time += play_time
        user_stats.save()