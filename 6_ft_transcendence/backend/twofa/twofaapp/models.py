from django.db import models


# Create your models here.


class User(models.Model):
    id = models.BigAutoField(primary_key=True)

    class Meta:
        db_table = "user"
        managed = False


class UserInfo(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, primary_key=True)
    twofa_secret = models.CharField(max_length=32)
    twofa_name = models.CharField(max_length=32)
    twofa_passed = models.BooleanField(default=False)
    twofa_stored = models.BooleanField(default=False)

    class Meta:
        db_table = "userinfo"
