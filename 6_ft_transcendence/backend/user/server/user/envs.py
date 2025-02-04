import os

def get_os_str(key):
    value = os.getenv(key)
    print(f"value: {value}")
    if value is None:
        raise KeyError(f"Environment variable '{key}' is missing")
    return value

JWT_URL = get_os_str("JWT_URL")