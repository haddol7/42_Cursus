import json as j
from logging import Logger
from typing import Any

import requests

from exceptions.CustomException import InternalException


logger = Logger(__name__)


def post(url: str, json: dict[str, Any]):
    try:
        logger.info(f"post to url={url}, json={j.dumps(json)}")
        return requests.post(url, json=json)
    except Exception as e:
        logger.exception(e)
        raise InternalException()


def get(url: str, params: dict[str, Any]):
    try:
        logger.info(f"get to url={url}, params={j.dumps(params)}")
        return requests.get(url, params=params)
    except Exception as e:
        logger.exception(e)
        raise InternalException()
