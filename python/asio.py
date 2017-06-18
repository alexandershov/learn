from collections import deque
from collections import namedtuple
import datetime
import heapq
import logging
import time


class Task:
    def __init__(self):
        self._callbacks = deque()

    def add_callback(self, callback):
        self._callbacks.append(callback)

    def callback(self, value):
        while self._callbacks:
            callback = self._callbacks.popleft()
            value = callback(value)
            if isinstance(value, Task):
                value.add_callback(self.callback)
                return value
        return value


Event = namedtuple('Event', ['call_time', 'fn'])


class EventLoop:
    def __init__(self):
        self._events = []

    def call_later(self, delay, fn):
        call_time = datetime.datetime.utcnow() + datetime.timedelta(seconds=delay)
        event = Event(call_time, fn)
        heapq.heappush(self._events, event)

    def start(self):
        while self._events:
            first = self._events[0]
            now = datetime.datetime.utcnow()
            if first.call_time <= now:
                event = heapq.heappop(self._events)
                event.fn()
            else:
                sleep_duration = (first.call_time - now).total_seconds()
                logging.info('sleeping for %s', sleep_duration)
                time.sleep(sleep_duration)


def test_task():
    values = []
    d = Task()
    d.add_callback(lambda v: values.append(v))
    assert d.callback(3) is None
    assert values == [3]


def test_callback_returns_task():
    values = [2, 1, 3]
    res = []
    count_task = Task()
    count_task.add_callback(lambda _: len(values))
    main_task = Task()
    main_task.add_callback(lambda _: count_task)
    main_task.add_callback(lambda num: res.append(bool(num % 2)))
    main_task.callback(None)
    count_task.callback(None)
    assert res == [1]


def test_event_loop():
    values = []
    loop = EventLoop()
    loop.call_later(0.03, lambda: values.append(3))
    loop.call_later(0.02, lambda: values.append(2))
    loop.call_later(0.04, lambda: values.append(4))
    loop.start()
    assert values == [2, 3, 4]
