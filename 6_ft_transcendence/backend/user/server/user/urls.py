from django.urls import path
from user import views

urlpatterns = [
    path('', views.ProfileDetail.as_view(), name='profile'),
    #path('friend/', views.friend),
]