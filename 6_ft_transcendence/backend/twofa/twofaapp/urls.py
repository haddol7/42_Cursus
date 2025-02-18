from django.urls import path

from twofaapp import views

urlpatterns = [
    path("info", views.handle_info),
    path("code", views.post_code),
    path("check", views.handle_check),
]
