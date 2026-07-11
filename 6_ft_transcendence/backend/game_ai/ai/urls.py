from django.urls import path

from ai import views

urlpatterns = [path("", views.post_ai)]
