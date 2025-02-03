from django.db import models
from django.utils.timezone import now

# Create your models here.


class User(models.Model):
    id = models.BigAutoField(primary_key=True)
    username = models.CharField(max_length=10, unique=True)

    class Meta:
        db_table = "user"
        managed = False


class TempMatchRoom(models.Model):
    id = models.BigAutoField(primary_key=True)
    room_name = models.CharField(max_length=32, unique=True)
    start_at = models.DateTimeField(default=now)
    end_at = models.DateTimeField(null=True, default=None)

    class Meta:
        db_table = "temp_match_room"


class TempMatchRoomUser(models.Model):
    user = models.OneToOneField(to=User, on_delete=models.CASCADE)
    temp_match_room = models.ForeignKey(to=TempMatchRoom, on_delete=models.CASCADE)

    is_online = models.BooleanField(default=False)
    # sid = models.CharField(max_length=32)

    class Meta:
        db_table = "temp_match_room_user"


class RoundEnum(models.IntegerChoices):
    TWO = 2, "Two"
    FOUR = 4, "Four"
    EIGHT = 8, "Eight"
    SIXTEEN = 16, "SIXTEEN"


class TempMatch(models.Model):
    id = models.BigAutoField(primary_key=True)
    winner = models.ForeignKey(User, on_delete=models.CASCADE, null=True, default=None)
    match_room = models.ForeignKey(TempMatchRoom, on_delete=models.CASCADE)
    round = models.IntegerField(choices=RoundEnum.choices)
    start_at = models.DateTimeField(default=now)
    end_at = models.DateTimeField(null=True, default=None)

    winner_match = models.ForeignKey("self", on_delete=models.CASCADE, null=True)

    joined_user = models.IntegerField(default=0)

    class Meta:
        db_table = "temp_match"


class TempMatchUser(models.Model):
    id = models.BigAutoField(primary_key=True)
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    temp_match = models.ForeignKey(TempMatch, on_delete=models.CASCADE)

    score = models.IntegerField(default=0)

    class Meta:
        db_table = "temp_match_user"
