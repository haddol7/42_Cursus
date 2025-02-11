from django.urls import path
from user import views

urlpatterns = [
    path('', views.ProfileDetail.as_view(), name='profile'),
    path('friend', views.FriendView.as_view(), name='friend'),
<<<<<<< HEAD
    path('dashboard', views.DashBoardView.as_view(), name='dashboard'),
=======
    path('dashboard', views.DashboardView.as_view(), name='dashboard'),
>>>>>>> backend/feat/user-test
]
