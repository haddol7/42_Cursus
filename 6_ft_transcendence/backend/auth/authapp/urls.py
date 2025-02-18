from django.urls import path

from authapp import views

urlpatterns = [
    # path("42/auth", views.get_42_oauth),
    path("42/code", views.get_42_code),
    path("refresh", views.refresh_token),
    path("2fa", views.handle_2fa),
    path("2fa/new", views.post_2fa_new),
    path("logout", views.logout),
    path("42/code/mock", views.get_42_code_mock),
    path("2fa/mock", views.mock_2fa),
]
