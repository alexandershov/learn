from collections import namedtuple
import datetime
import heapq
import logging
import time


class Task:
    def __init__(self):
        self._callbacks = []
    
    def add_callback(self, callback):
        self._callbacks.append(callback)

    def callback(self, value):
        for callback in self._callbacks:
            value = callback(value)
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


def test_event_loop():
    values = []
    loop = EventLoop()
    loop.call_later(0.3, lambda: values.append(3))
    loop.call_later(0.2, lambda: values.append(2))
    loop.call_later(0.4, lambda: values.append(4))
    loop.start()
    assert values == [2, 3, 4]
