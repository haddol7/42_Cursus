from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.parsers import MultiPartParser, FormParser, FileUploadParser, JSONParser
from rest_framework.request import Request
from rest_framework import status
#from rest_framework import generics

import requests
from .models import Profile
from .serializers import ProfileSerializer
from django.shortcuts import get_object_or_404


class ProfileDetail(APIView):
    parser_classes = [JSONParser, FileUploadParser]

    def get(self, request, format=None):
        user_name: str = request.query_params.get('user_name')  # ?user_name=<name>에서 <name> 가져오기
        if not user_name:
            return Response({"error": "user_name query parameter is required"}, status=status.HTTP_400_BAD_REQUEST)
        else:
            print(user_name)
        
        user = Profile.objects.filter(nickname=user_name).first()
        if not user:
            print("No user!")
            # jwt 토큰 jwt 서버에서 조회후, user_id 받아서 Profile user_id에 저장!
            profile = Profile.objects.create(user_id='jwt:user_id', nickname=user_name)
            profile.save()

        serializer = ProfileSerializer(user)
        return Response(serializer.data)

    def put(self, request, format=None):
        # jwt 서버에 요청해서 user_id 받아서 프로필 목록에서 조회! 
        _user = request.user
        user = get_object_or_404(Profile, user_id=_user.user_id)
        serializer = ProfileSerializer(user, data=request.data, partial=True)  # partial=True로 일부분 업데이트 허용
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, format=None):
        # user_name = request.query_params.get('user_name')
        # if not user_name:
        #     return Response({"error": "username query parameter is required"}, status=status.HTTP_400_BAD_REQUEST)

        _user = request.user
        user = get_object_or_404(Profile, user_id=_user.user_id)
        user.delete()
        return Response({"message": "User deleted successfully"}, status=status.HTTP_204_NO_CONTENT)
