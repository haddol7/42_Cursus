from rest_framework import serializers
from user.models import Profile, Friend, DashBoard

class ProfileSerializer(serializers.ModelSerializer):
    class Meta:
        model = Profile 
        fields = ['user_id', 'user_name', 'memo', 'image_url']

class FriendSerializer(serializers.ModelSerializer):
    friend = ProfileSerializer()

    class Meta:
        model = Friend 
        fields = ['friend']


class TopRankingSerializer(serializers.ModelSerializer):
    user_name = serializers.CharField(source='_user.user_name')
    image_url = serializers.ImageField(source='_user.image_url')
    win_cnt = serializers.IntegerField(source='win_cnt')
    total_cnt = serializers.IntegerField(source='total_cnt')

    class Meta:
        model = DashBoard
        fields = ['user_name', 'image_url', 'win_cnt', 'total_cnt']


class DashBoardSerializer(serializers.ModelSerializer):
    top_ranking = serializers.SerializerMethodField()

    class Meta:
        model = DashBoard
        fields = ['win_cnt', 'total_cnt', 'top_ranking']

    def get_top_ranking(self, obj):
        # 승리 수 기준 상위 3명의 유저를 반환
        top_users = DashBoard.objects.order_by('-win_cnt', 'total_cnt')[:3]
        return TopRankingSerializer(top_users, many=True).data
