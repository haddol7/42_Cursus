from rest_framework import serializers
from .models import Profile

class ProfileSerializer(serializers.ModelSerializer):
    class Meta:
        model = Profile 
        fields = ['user_id', 'nickname', 'memo', 'image_url', 'win_cnt', 'lose_cnt', 'created_at']
