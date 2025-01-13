from django.urls import path

from . import views

urlpatterns = [
    path("", views.apiRedirected, name="apiRedirected"),
    path("login", views.loginTo42, name="loginTo42"),
    path("jwt", views.makeJWT, name="makeJWT"),
    path("decodejwt", views.decodeJWT, name="decodeJWT"),
    path("helper", views.helper, name="helper"),
    path("validate_totp", views.validate_totp, name="validate_totp"),
]
