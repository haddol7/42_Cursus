from django.urls import path

from . import views

urlpatterns = [
    path("check", views.check_jwt_request),
    path("refresh", views.refresh_jwt),
    path("token", views.handle_token),
    path("online", views.get_online),
    path("token/ai", views.post_token_ai),
    path("check/ai", views.post_check_ai),
]
