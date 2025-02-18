from django.urls import path

from . import views

urlpatterns = [path("game", views.handle_game)]
public_patterns = [path("ai", views.post_aigame)]
