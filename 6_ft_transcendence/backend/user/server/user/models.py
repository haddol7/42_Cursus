from django.db import models

class Profile(models.Model):
    user_id = models.AutoField(primary_key=True)
    user_name = models.CharField(max_length=50, null=True, unique=True)
    memo = models.TextField(max_length=500, blank=True)
    image_url = models.ImageField(default='default.png', upload_to='images/')

    class Meta:
        db_table = "profile"


class Friend(models.Model):
    user = models.OneToOneField(Profile, on_delete=models.CASCADE, related_name='friends')
    friends = models.ManyToManyField('self', blank=True, symmetrical=False)

    class Meta:
        db_table = "friends"
    
# response = requests.post('http://127.0.0.1:8100/jwt/check', json={"jwt": "value"})
# print(response.json())