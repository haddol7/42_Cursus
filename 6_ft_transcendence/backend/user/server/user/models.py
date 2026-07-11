from django.db import models

class Profile(models.Model):
    user_id = models.AutoField(primary_key=True)
    user_name = models.CharField(max_length=50, unique=True, blank=False, default='default_user')
    memo = models.TextField(blank=True) 
    win_cnt = models.PositiveIntegerField(default=0)
    lose_cnt = models.PositiveIntegerField(default=0)
    total_cnt = models.PositiveIntegerField(default=0)

    image_url = models.ImageField(upload_to='', default='default.png')

    class Meta:
        db_table = "profile"


class Friend(models.Model):
    _user = models.ForeignKey(Profile, on_delete=models.CASCADE, related_name='following')
    friend = models.ForeignKey(Profile, on_delete=models.CASCADE, related_name='followers', null=True)

    class Meta:
        db_table = "friends"
        constraints = [
            models.UniqueConstraint(fields=['_user', 'friend'], name='unique_friendship')
        ]


class UserStats(models.Model):
    user = models.OneToOneField(Profile, on_delete=models.CASCADE, related_name="stats")
    total_games = models.PositiveIntegerField(default=0)
    win_cnt = models.PositiveIntegerField(default=0)
    lose_cnt = models.PositiveIntegerField(default=0)
    total_play_time = models.PositiveIntegerField(default=0)

    class Meta:
        db_table = "user_stats"


class MatchHistory(models.Model):
    player1_id = models.ForeignKey(Profile, on_delete=models.CASCADE, related_name="player1_matches")
    player2_id = models.ForeignKey(Profile, on_delete=models.CASCADE, related_name="player2_matches")
    player1_score = models.PositiveIntegerField()
    player2_score = models.PositiveIntegerField()
    winner_id = models.ForeignKey(Profile, on_delete=models.CASCADE, related_name="won_matches")
    match_date = models.DateTimeField()
    play_time = models.PositiveIntegerField()

    class Meta:
        db_table = "match_history"
        ordering = ["-match_date"]


class WinRateTrend(models.Model):
    user = models.ForeignKey(Profile, on_delete=models.CASCADE, related_name="win_rate_trend")
    game_number = models.PositiveIntegerField()
    win_rate = models.FloatField()
    
    class Meta:
        db_table = "win_rate_trend"
        unique_together = ("user", "game_number")
