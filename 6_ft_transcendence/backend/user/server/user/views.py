from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.parsers import FileUploadParser, JSONParser
from rest_framework.request import Request
from rest_framework import status
import requests
from user.models import Profile, Friend, DashBoard
from user.serializers import ProfileSerializer, FriendSerializer, DashBoardSerializer
from django.shortcuts import get_object_or_404
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
            return Response(res.content, status=res.status_code)
        res = res.json()
        return int(res["user_id"]) 

# /user
class ProfileDetail(APIView, JWTAuthenticationMixin):
    parser_classes = [JSONParser, FileUploadParser]

    def get(self, req: Request):
        try:
            #print("get request start!")
            user_id = self.check_jwt(req)
            #print(f"check jwt end! user_id:{user_id}")
            user_name: str = req.query_params.get('user_name')  # ?user_name=<name>에서 <name> 가져오기
            if not user_name:
                return Response({"error": "user_name query parameter is required"}, status=status.HTTP_400_BAD_REQUEST)
            
            user = Profile.objects.filter(user_name=user_name).first()
            if not user:
                profile = Profile.objects.create(user_id=user_id, user_name=user_name)
                profile.save()
                serializer = ProfileSerializer(profile)
                return Response(serializer.data, status=status.HTTP_201_CREATED)

            serializer = ProfileSerializer(user)
            return Response(serializer.data)
        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

    def put(self, req: Request):
        try:
            user_id = self.check_jwt(req)
            user = get_object_or_404(Profile, user_id=user_id)
            serializer = ProfileSerializer(user, data=req.data, partial=True)  # partial=True로 일부분 업데이트 허용
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
            user_profile = get_object_or_404(Profile, user_id=user_id)
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
            user_profile = get_object_or_404(Profile, user_id=user_id)
            friend_name = req.data.get('user_name')
            if not friend_name:
                return Response({'error': 'user_name field is required.'}, status=status.HTTP_400_BAD_REQUEST)

            friend_profile = get_object_or_404(Profile, user_name=friend_name) # 친구 프로필 조회

            if user_profile.user_id == friend_profile.user_id:
                return Response({'error': 'You cannot add yourself as a friend.'}, status=status.HTTP_400_BAD_REQUEST)

            if Friend.objects.filter(_user=user_profile, friend=friend_profile).exists():
                return Response({'error': f'{friend_name} is already your friend.'}, status=status.HTTP_400_BAD_REQUEST)

            Friend.objects.create(_user=user_profile, friend=friend_profile)
            return Response({'message': f'{friend_name} has been added as your friend.'}, status=status.HTTP_201_CREATED)

        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

class DashBoardView(APIView, JWTAuthenticationMixin):
    def get(self, req: Request):
        try:
            user_id = self.check_jwt(req)
            user_profile = get_object_or_404(Profile, user_id=user_id)

            dashboard, created = DashBoard.objects.get_or_create(_user=user_profile)

            serializer = DashBoardSerializer(dashboard)
            return Response(serializer.data, status=status.HTTP_200_OK)

        except PermissionError as e:
            return Response({'error': str(e)}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({'error': 'Internal Server Error.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
        