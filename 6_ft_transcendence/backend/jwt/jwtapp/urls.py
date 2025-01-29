from django.urls import path
from . import views

urlpatterns = [
    path("check", views.check_jwt_request),
    path("refresh", views.refresh_jwt),
    path("token", views.handle_token),
]
