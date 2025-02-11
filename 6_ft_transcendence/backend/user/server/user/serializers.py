from rest_framework import serializers
from user.models import Profile, Friend

class ProfileSerializer(serializers.ModelSerializer):
    class Meta:
        model = Profile 
        fields = ['user_name', 'memo', 'win_cnt', 'lose_cnt', 'total_cnt', 'image_url']

    def validate_user_name(self, value):
        if self.instance:
            # 업데이트 모드: 기존 인스턴스를 제외하고 중복 체크
            if Profile.objects.exclude(pk=self.instance.pk).filter(user_name=value).exists():
                raise serializers.ValidationError("This user name already exists.")
        else:
            # 생성 모드: 전체에서 중복 체크
            if Profile.objects.filter(user_name=value).exists():
                raise serializers.ValidationError("This user name already exists.")
        return value




class FriendSerializer(serializers.ModelSerializer):
    user_name = serializers.CharField(source='friend.user_name')

    class Meta:
        model = Friend 
        fields = ['user_name'] 
