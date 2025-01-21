from django.urls import path

from authapp import views


urlpatterns = [
    path("42/oauth", views.get_42_oauth),
    path("42/code", views.get_42_code),
    path("refresh", views.refresh_token),
]
