from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.parsers import MultiPartParser, FormParser
from rest_framework import status
#from rest_framework import generics
from .models import Profile
from .serializers import ProfileSerializer
from django.shortcuts import get_object_or_404


class ProfileDetail(APIView):
    def get(self, request):
        user_name = request.query_params.get('user_name')  # ?user_name=<name>에서 <name> 가져오기
        if not user_name:
            return Response({"error": "user_name query parameter is required"}, status=status.HTTP_400_BAD_REQUEST)
        
        #user = get_object_or_404(Profile, nickname=user_name)
        user = Profile.objects.filter(nickname=user_name).first()
        # if not user:
        #     print("user none!")
        #     profile = Profile.objects.create(nickname=user_name)
        #     profile.save()

        # print("user exist!")
        serializer = ProfileSerializer(user)
        return Response(serializer.data)

    def put(self, request):
        user_name = request.query_params.get('user_name')
        if not user_name:
            return Response({"error": "user_name query parameter is required"}, status=status.HTTP_400_BAD_REQUEST)

        user = get_object_or_404(Profile, nickname=user_name)
        serializer = ProfileSerializer(user, data=request.data, partial=True)  # partial=True로 부분 업데이트 허용
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request):
        user_name = request.query_params.get('user_name')
        if not user_name:
            return Response({"error": "username query parameter is required"}, status=status.HTTP_400_BAD_REQUEST)

        user = get_object_or_404(Profile, nickname=user_name)
        user.delete()
        return Response({"message": "User deleted successfully"}, status=status.HTTP_204_NO_CONTENT)
