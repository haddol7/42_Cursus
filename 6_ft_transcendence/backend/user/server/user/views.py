from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.parsers import FileUploadParser, JSONParser
from rest_framework.request import Request
from rest_framework import status
import requests
from user.models import Profile, Friend, DashBoard
from user.serializers import ProfileSerializer, FriendSerializer, DashBoardSerializer
from user.envs import JWT_URL


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
            raise PermissionError("error: No login user.")
        res = res.json()
        return int(res["user_id"]) 


# /user
class ProfileDetail(APIView, JWTAuthenticationMixin):
    parser_classes = [JSONParser, FileUploadParser]

    def get(self, req: Request):
        try:
            user_id = self.check_jwt(req)
            user_name: str = req.query_params.get('user_name')  # ?user_name=<name>에서 <name> 가져오기
            if not user_name:
                return Response({"error": "user_name query parameter is required"}, status=status.HTTP_400_BAD_REQUEST)
            
            user = Profile.objects.filter(user_name=user_name).first()

            #Todo: fix to Response 404 NOT FOUND
            # if not user:
            #     profile = Profile.objects.create(user_id=user_id, user_name=user_name)
            #     profile.save()
            #     serializer = ProfileSerializer(profile)
            #     return Response(serializer.data, status=status.HTTP_201_CREATED)
            if not user:
                return Response({'error':'user_name is not found.'}, status=status.HTTP_404_NOT_FOUND)

            serializer = ProfileSerializer(user)
            return Response(serializer.data)
        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

    def put(self, req: Request):
        try:
            user_id = self.check_jwt(req)
            user_profile = Profile.objects.filter(user_id=user_id).first()
            if not user_profile:
                return Response({'error': 'user_profile is not found.'}, status=status.HTTP_404_NOT_FOUND)

            user_name = req.data.get('user_name')
            if Profile.objects.filter(user_name=user_name).exists():
                return Response({'error': f'{user_name} is already exist.'}, status=status.HTTP_400_BAD_REQUEST)

            serializer = ProfileSerializer(user_profile, data=req.data, partial=True)  # partial=True로 일부분 업데이트 허용
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data)
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

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
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
        

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
                return Response({'error': 'friend_name is not found.'}, status=status.HTTP_404_NOT_FOUND)

            if user_profile.user_id == friend_profile.user_id:
                return Response({'error': 'You cannot add yourself as a friend.'}, status=status.HTTP_400_BAD_REQUEST)

            if Friend.objects.filter(_user=user_profile, friend=friend_profile).exists():
                return Response({'error': f'{friend_name} is already your friend.'}, status=status.HTTP_400_BAD_REQUEST)

            Friend.objects.create(_user=user_profile, friend=friend_profile)
            return Response({'message': f'{friend_name} is successfully added as your friend.'}, status=status.HTTP_201_CREATED)

        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)


# /user/dashboard
class DashBoardView(APIView, JWTAuthenticationMixin):
    def get(self, req: Request):
        try:
            user_id = self.check_jwt(req)
            user_profile = Profile.objects.filter(user_id=user_id).first()
            if not user_profile:
                return Response({'error': 'user_profile is not found.'}, status=status.HTTP_404_NOT_FOUND)

            dashboard, created = DashBoard.objects.get_or_create(_user=user_profile)
            serializer = DashBoardSerializer(dashboard)
            print(f"serializer.data: {serializer}")
            return Response(serializer.data, status=status.HTTP_200_OK)

        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
        

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
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

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
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

#/_internal/dashboard
class InternalDashBoardView(APIView):
    parser_classes = [JSONParser]

    def post(slef, req: Request):
        try:
            user_id = req.data.get('user_id')
            if not user_id:
                return Response({'error':'user_id is required.'}, status=status.HTTP_400_BAD_REQUEST)
            result = req.data.get('result')
            if not result:
                return Response({'error':'result is required.'}, status=status.HTTP_400_BAD_REQUEST)

            profile = Profile.objects.filter(user_id=user_id).first()
            dashboard, created = DashBoard.objects.get_or_create(_user=profile)
            dashboard.total_cnt += 1
            if result == 'win':
                dashboard.win_cnt += 1
            dashboard.save()
            return Response({'message': 'User stats updated successfully'})
        except Exception as e:
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
