import threading
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from .match import Match


TIMEOUT_SEC = 10


class WaitingProcess(threading.Thread):
    def __init__(self, match: "Match"):
        super().__init__()
        self.event = threading.Event()
        self.time_out = False
        self.match = match

    def run(self):
        print("WatingProcess - Run start")
        self.event.wait(TIMEOUT_SEC)
        if self.event.is_set():
            return
        self.time_out = True
        self.event.set()
        self.match.timed_out()

    def stop(self):
        print("WaitingProcess - Run Stopped")
        self.event.set()

    def is_time_out(self) -> bool:
        if not self.event.is_set():
            return False
        return self.time_out
