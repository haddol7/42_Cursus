import json as j
import logging
from typing import Any

import requests

from exceptions.CustomException import InternalException

logger = logging.getLogger(__name__)


def post(
    url: str, json: dict[str, Any] | None = None, data: dict[str, Any] | None = None
):
    try:
        logger.info(f"post to url={url}, json={j.dumps(json)}, data={j.dumps(data)}")
        return requests.post(url, json=json, data=data)
    except Exception as e:
        logger.error(e)
        raise InternalException()


def get(
    url: str,
    params: dict[str, Any] | None = None,
    headers: dict[str, Any] | None = None,
):
    try:
        logger.info(
            f"get to url={url}, params={j.dumps(params)}, headers={j.dumps(headers)}"
        )
        return requests.get(url, params=params, headers=headers)
    except Exception as e:
        logger.error(e)
        raise InternalException()


def delete(url: str, params: dict[str, Any] | None = None):
    try:
        logger.info(f"delete to url={url}, params={j.dumps(params)}")
        return requests.delete(url, params=params)
    except Exception as e:
        logger.error(e)
        raise InternalException()
