from django.db import models
#from django.contrib.auth.models import User

class Profile(models.Model):
    #user = models.OneToOneField(User, on_delete=models.CASCADE, primary_key=True)
    user_id = models.AutoField(primary_key=True)
    nickname = models.CharField(max_length=50, null=True, unique=True)
    memo = models.TextField(max_length=500, blank=True)
    win_cnt = models.IntegerField(default=0)
    lose_cnt = models.IntegerField(default=0)


    # image url경로만 지정
    image_url = models.ImageField(default='default.png', upload_to='images/')
    created_at = models.DateTimeField(auto_now_add=True)

    class Meta:
        db_table = "profile"


class Friend(models.Model):
    user = models.OneToOneField(Profile, on_delete=models.CASCADE, related_name='friends')
    friends = models.ManyToManyField('self', blank=True, symmetrical=False)

    class Meta:
        db_table = "friends"
    
