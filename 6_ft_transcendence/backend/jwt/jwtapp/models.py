from django.db import models

# Create your models here.


class User(models.Model):
    id = models.AutoField(primary_key=True)
    username = models.CharField(max_length=10)
    profile_url = models.CharField(max_length=128)
    created_at = models.DateTimeField()

    class Meta:
        db_table = "user"


class UserInfo(models.Model):
    user_id = models.OneToOneField(User, on_delete=models.CASCADE, primary_key=True)
    twofa_secret = models.CharField(max_length=15)
    twofa_name = models.CharField(max_length=32)

    class Meta:
        db_table = "userinfo"


class UserStatus(models.Model):
    user_id = models.OneToOneField(User, on_delete=models.CASCADE, primary_key=True)
    jwt_secret = models.CharField(max_length=10)
    refresh_secret = models.CharField(max_length=10)
    expired_at = models.DateTimeField()

    class Meta:
        db_table = "user_status"
