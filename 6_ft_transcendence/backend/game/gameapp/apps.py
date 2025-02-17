from django.apps import AppConfig
from requests import delete


class GameappConfig(AppConfig):
    default_auto_field = "django.db.models.BigAutoField"
    name = "gameapp"

    def ready(self):
        # importing model classes
        from .models import TempMatchUser, TempMatch, TempMatchRoomUser, TempMatchRoom

        TempMatchUser.objects.all().delete()
        TempMatch.objects.all().delete()
        TempMatchRoomUser.objects.all().delete()
        TempMatchRoom.objects.all().delete()
