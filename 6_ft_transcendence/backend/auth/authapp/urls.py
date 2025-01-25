from django.urls import path

from authapp import views


urlpatterns = [
    path("42/code", views.get_42_code),
    path("refresh", views.refresh_token),
    path("2fa", views.handle_2fa),
    path("logout", views.logout),
]
