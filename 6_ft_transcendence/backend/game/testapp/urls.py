from django.urls import path

from testapp import views


urlpatterns = [path("make_rooms", views.make_rooms_post)]
