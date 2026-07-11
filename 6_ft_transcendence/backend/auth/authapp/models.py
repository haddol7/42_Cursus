from django.db import models


# Create your models here.


class User(models.Model):
    id = models.BigAutoField(primary_key=True)
    id_42 = models.BigIntegerField(unique=True)

    class Meta:
        db_table = "user"
