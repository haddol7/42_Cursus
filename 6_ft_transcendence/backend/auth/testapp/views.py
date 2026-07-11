import random
from typing import Any, Dict
from django.http import JsonResponse
from django.shortcuts import render

from authapp.decorators import api_post

from rest_framework.request import Request

from authapp.models import User
from authapp.utils import get_str, now

# Create your views here.


@api_post
def post_user(req: Request, data: Dict[str, Any]):
    username = get_str(data, "username")
    User.objects.create(
        id_42=int(random.random() * 1000000) + 1000000,
        username=username,
        profile_url="",
        created_at=now(),
    )
    return JsonResponse({})
