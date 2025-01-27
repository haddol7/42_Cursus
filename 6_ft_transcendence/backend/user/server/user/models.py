from django.db import models
from django.db.models.signals import post_save
from django.contrib.auth.models import User
from django.dispatch import receiver
import requests

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

    @receiver(post_save, sender=User)
    def create_user_profile(sender, instance, created, **kwargs):
        if created:
            Profile.objects.create(user=instance)    

    @receiver(post_save, sender=User)
    def save_user_profile(sender, instance, **kwargs):
        instance.profile.save()

    # response = requests.post('http://127.0.0.1:8100/jwt/check', json={"jwt": "value"})
    # print(response.json())


class Friend(models.Model):
    user = models.OneToOneField(Profile, on_delete=models.CASCADE, related_name='friends')
    friends = models.ManyToManyField('self', blank=True, symmetrical=False)

    class Meta:
        db_table = "friends"
    
# def authenticated(skip_2fa=False):
#     def _func(func):
#         def wrapper(req: HttpRequest, *args, **kwargs):
#             if "Authorization" not in req.headers:
#                 raise UnauthenticatedException()

#             authorization_header: str = req.headers["Authorization"]
#             if not authorization_header.startswith("Bearer "):
#                 raise UnauthenticatedException()

#             jwt = authorization_header[7:]
#             res = requests.post(
#                 f"{JWT_URL}/jwt/check", json={"jwt": jwt, "skip_2fa": skip_2fa}
#             )
#             if not res.ok:
#                 return HttpResponse(res.content, status=res.status_code)

#             res = res.json()
#             return func(req, user_id=int(res["user_id"]), *args, *kwargs)

#         return wrapper

#     return _func