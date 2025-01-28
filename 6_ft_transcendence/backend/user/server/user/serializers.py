from rest_framework import serializers
from .models import Profile, Friend

class ProfileSerializer(serializers.ModelSerializer):
    class Meta:
        model = Profile 
        fields = ['user_id', 'user_name', 'memo', 'image_url']

class FriendSerializer(serializers.ModelSerializer):
    class Meta:
        model = Friend 
        fields = ['friends']