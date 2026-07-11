from django.db import models


# Create your models here.


class User(models.Model):
    id = models.BigAutoField(primary_key=True)

    class Meta:
        db_table = "user"
        managed = False


class UserStatus(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, primary_key=True)
    jwt_secret = models.CharField(max_length=10)
    refresh_secret = models.CharField(max_length=10)
    expired_at = models.DateTimeField()

    class Meta:
        db_table = "user_status"
