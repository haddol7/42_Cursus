class CustomException(Exception):
    def __init__(self, msg: str):
        self.msg = msg

    def __format__(self, _format: str):
        return self.msg
