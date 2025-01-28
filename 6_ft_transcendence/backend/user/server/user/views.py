from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.parsers import FileUploadParser, JSONParser
from rest_framework.request import Request
from rest_framework import status
import requests
from user.models import Profile, Friend
from user.serializers import ProfileSerializer, FriendSerializer
from django.shortcuts import get_object_or_404
from user.envs import JWT_URL

# /user
class ProfileDetail(APIView):
    parser_classes = [JSONParser, FileUploadParser]

    def check_jwt(self, req: Request):
        if "Authorization" not in req._request.headers:
            return Response({"error": "Authorization header is missing"}, status=status.HTTP_401_UNAUTHORIZED)
        authorization_header: str = req._request.headers["Authorization"]
        if not authorization_header.startswith("Bearer "):
            return Response({"error": "Invalid Authorization header"}, status=status.HTTP_401_UNAUTHORIZED)
        jwt = authorization_header[7:] 
        res = requests.post(
            f"{JWT_URL}/jwt/check", json={"jwt": jwt, "skip_2fa": True}
        )
        if not res.ok:
            return Response(res.content, status=res.status_code)
        res = res.json()
        return int(res["user_id"]) 

    def get(self, req: Request):
        print("get request start!")
        user_id = self.check_jwt(req)
        print(f"check jwt end! user_id:{user_id}")
        user_name: str = req.query_params.get('user_name')  # ?user_name=<name>에서 <name> 가져오기
        if not user_name:
            return Response({"error": "user_name query parameter is required"}, status=status.HTTP_400_BAD_REQUEST)
        
        user = Profile.objects.filter(user_name=user_name).first()
        if not user:
            # jwt 토큰 jwt 서버에서 조회후, user_id 받아서 Profile user_id에 저장!
            profile = Profile.objects.create(user_id=user_id, user_name=user_name)
            profile.save()
            serializer = ProfileSerializer(profile)
            return Response(serializer.data, status=status.HTTP_201_CREATED)

        serializer = ProfileSerializer(user)
        return Response(serializer.data)

    def put(self, req: Request):
        user_id = self.check_jwt(req)
        user = get_object_or_404(Profile, user_id=user_id)
        serializer = ProfileSerializer(user, data=req.data, partial=True)  # partial=True로 일부분 업데이트 허용
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


# /user/friend
class FriendList(APIView):
    parser_classes = [JSONParser]

    def get(self, req :Request):
        friends = Friend.objects.values_list('user_name', flat=True)
        return Response({"user_names": list(friends)}, status=status.HTTP_200_OK)

    def post(self, req :Request):
        serializer = FriendSerializer(data=req.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)