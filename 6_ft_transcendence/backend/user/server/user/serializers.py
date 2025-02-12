from rest_framework import serializers
from user.models import Profile, Friend
import re
import string

class ProfileSerializer(serializers.ModelSerializer):

    class Meta:
        model = Profile 
        fields = ['user_name', 'memo', 'win_cnt', 'lose_cnt', 'total_cnt', 'image_url']

    def validate_user_name(self, value): # 'user_name' 검증
        if len(value) < 4:
            raise serializers.ValidationError("User name too short. It must be at least 3 characters.")

        if re.search(r'[^a-zA-Z0-9가-힣 ]', value): # (a-z, A-Z, 0-9, 가-힣) 를 제외한 문자가 있는지 검사하고 있으면 에러 발생.
            raise serializers.ValidationError("User name cannot contain special characters.")

        if self.instance:
            # 본인 user_name을 제외하고 중복 체크 (PUT) 
            if Profile.objects.exclude(pk=self.instance.pk).filter(user_name=value).exists():
                raise serializers.ValidationError("This user name already exists.")
        else:
            # 전체에서 중복 체크 (POST) -> 다수의 유저가 최초 로그인시 체크됨.
            if Profile.objects.filter(user_name=value).exists():
                raise serializers.ValidationError("This user name already exists.")
        return value
    
    def validate_memo(self, value): # 'memo' 검증, 최대 500자
        if len(value) > 500:
            raise serializers.ValidationError("Memo cannot exceed 500 characters.")
        return value




class FriendSerializer(serializers.ModelSerializer):
    user_name = serializers.CharField(source='friend.user_name')

    class Meta:
        model = Friend 
        fields = ['user_name'] 
