from django.urls import path

from testapp import views


urlpatterns = [path("user", views.post_user)]
