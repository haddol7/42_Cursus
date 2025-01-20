from django.urls import path
from . import views

urlpatterns = [
    path("check", views.check_jwt_request),
    path("refresh", views.refresh_jwt),
    path("new", views.make_new_jwt),
    path("user", views.make_user),
]
