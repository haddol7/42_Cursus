from rest_framework import serializers
from user.models import Profile, Friend, DashBoard

class ProfileSerializer(serializers.ModelSerializer):
    class Meta:
        model = Profile 
        fields = ['user_name', 'memo', 'image_url', 'win_cnt', 'lose_cnt', 'total_cnt']

    def validate_user_name(self, value): # serializer.is_valid() 에서 호출
        instance = self.instance
        if Profile.objects.exclude(pk=instance.pk).filter(user_name=value).exists():
            raise serializers.ValidationError("It is already exist name.")
        return value


class FriendSerializer(serializers.ModelSerializer):
    user_name = serializers.CharField(source='friend.user_name')

    class Meta:
        model = Friend 
        fields = ['user_name'] 


class TopRankingSerializer(serializers.ModelSerializer):
    user_name = serializers.CharField(source='_user.user_name')
    image_url = serializers.ImageField(source='_user.image_url')

    class Meta:
        model = DashBoard
        fields = ['user_name', 'image_url', 'win_cnt', 'total_cnt']


class DashBoardSerializer(serializers.ModelSerializer):
    top_ranking = serializers.SerializerMethodField()

    class Meta:
        model = DashBoard
        fields = ['win_cnt', 'lose_cnt', 'total_cnt', 'top_ranking']

    @staticmethod
    def get_top_ranking(obj):
        top_users = DashBoard.objects.select_related('_user').order_by('-win_cnt', 'total_cnt')[:3]
        return TopRankingSerializer(top_users, many=True).data