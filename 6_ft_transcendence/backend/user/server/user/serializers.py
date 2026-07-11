from rest_framework import serializers
from user.models import Profile, Friend
import requests
import re
from user.envs import JWT_URL


class ProfileSerializer(serializers.ModelSerializer):

    class Meta:
        model = Profile 
        fields = ['user_name', 'memo', 'win_cnt', 'lose_cnt', 'total_cnt', 'image_url']

    def validate_user_name(self, value):
        if len(value) < 2:
            raise serializers.ValidationError("User name too short. It must be at least 2 characters.")

        if re.search(r'[^a-zA-Z0-9가-힣_]', value):
            raise serializers.ValidationError("User name cannot contain special characters or blank.")

        if self.instance:
            # 본인 user_name을 제외하고 중복 체크
            if Profile.objects.exclude(pk=self.instance.pk).filter(user_name=value).exists():
                raise serializers.ValidationError("This user name already exists.")
        else:
            # 전체에서 중복 체크 -> 다수의 유저가 최초 로그인시 체크됨.
            if Profile.objects.filter(user_name=value).exists():
                raise serializers.ValidationError("This user name already exists.")
        return value
    
    def validate_memo(self, value):
        if len(value) > 500:
            raise serializers.ValidationError("Memo cannot exceed 500 characters.")
        return value



class FriendSerializer(serializers.ModelSerializer):
    user_name = serializers.CharField(source='friend.user_name', read_only=True)
    online_status = serializers.SerializerMethodField()

    class Meta:
        model = Friend 
        fields = ['user_name', 'online_status'] 

    def get_online_status(self, value: Friend) -> bool:
        user_id = value.friend.user_id
        try:
            response = requests.get(f"{JWT_URL}/jwt/online", params={"user_id": user_id} ,timeout=2)
            if response.ok:
                res = response.json()
                return res["isonline"]
        except requests.RequestException:
            return False
        return False


