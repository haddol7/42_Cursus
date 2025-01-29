from django.db import models

# Create your models here.


class User(models.Model):
    id = models.BigAutoField(primary_key=True)
    id_42 = models.BigIntegerField(unique=True)
    username = models.CharField(max_length=10, unique=True)
    profile_url = models.CharField(max_length=128)
    created_at = models.DateTimeField()

    class Meta:
        db_table = "user"
