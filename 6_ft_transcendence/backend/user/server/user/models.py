from django.db import models

class Profile(models.Model):
    user_id = models.AutoField(primary_key=True)
    user_name = models.CharField(max_length=50, null=True, unique=True)
    memo = models.TextField(max_length=500, blank=True)
    image_url = models.ImageField(default='default.png', upload_to='images/')

    class Meta:
        db_table = "profile"


class Friend(models.Model):
    _user = models.ForeignKey(Profile, on_delete=models.CASCADE, related_name='following') # 팔로우하는 유저
    friend = models.ForeignKey(Profile, on_delete=models.CASCADE, related_name='followers', null=True) # 팔로우된 유저

    class Meta:
        db_table = "friends"
        constraints = [
            models.UniqueConstraint(fields=['_user', 'friend'], name='unique_friendship')
        ]


class DashBoard(models.Model):
    _user = models.OneToOneField(Profile, on_delete=models.CASCADE, related_name='dashboard')
    win_cnt = models.PositiveIntegerField(default=0)
    total_cnt = models.PositiveIntegerField(default=0)

    class Meta:
        db_table = "dashboard"
        ordering = ['-win_cnt', 'total_cnt'] # 승리수가 높은 유저부터 보여주기