import datetime
from authapp.models import User, UserInfo, UserStatus


def set_totp_secret(user_id: int, totp_secret: str, totp_name: str):
    user_obj, created = UserInfo.objects.update_or_create(
        user_id=User.objects.get(id=user_id),
        defaults={"twofa_secret": totp_secret, "twofa_name": totp_name},
        create_defaults={"twofa_secret": totp_secret, "twofa_name": totp_name},
    )
    print("user_obj, crated = ", user_obj, created)


def get_totp_secret(user_id: int):
    user_obj = UserInfo.objects.get(pk=User.objects.get(id=user_id))
    return user_obj.twofa_secret


def delete_jwt_secrets(user_id: int):
    user_status = UserStatus.objects.get(user_id=User.objects.get(id=user_id))
    user_status.jwt_secret = ""
    user_status.refresh_secret = ""
    user_status.expired_at = datetime.datetime.now(
        datetime.timezone.utc
    ) - datetime.timedelta(seconds=1)
    user_status.twofa_passed = False
    user_status.save()


def update_2fa_passed(user_id: int):
    user_status = UserStatus.objects.get(user_id=User.objects.get(id=user_id))
    user_status.twofa_passed = True
    user_status.save()
