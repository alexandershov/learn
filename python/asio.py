from collections import deque
from collections import namedtuple
from functools import wraps
import datetime
import heapq
import logging
import time
import types


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

def return_value(value):
    raise ReturnValue(value)


class ReturnValue(Exception):
    def __init__(self, value):
        self.value = value


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
                

def inline_callbacks(fn):
    @wraps(fn)
    def wrapper(*args, **kwargs):
        gen = fn(*args, **kwargs)
        assert isinstance(gen, types.GeneratorType)
        task = Task()
        
        def unwind_callbacks(value):
            try:
                new_value = gen.send(value)
            except ReturnValue as exc:
                task.callback(exc.value)
            except StopIteration as exc:
                task.callback(None)
            else:
                if isinstance(new_value, Task):
                    new_value.add_callback(lambda v: unwind_callbacks(v))
                    return
                else:
                    unwind_callbacks(new_value)
        unwind_callbacks(None)
        return task
    return wrapper


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


def test_inline_callbacks():
    res = []
    loop = EventLoop()
    logging.basicConfig(level=logging.INFO)
    def connect(address):
        result = Task()
        result.add_callback(lambda value: print('connected', address))
        loop.call_later(0.2, lambda: result.callback(None))
        return result
        
    @inline_callbacks
    def save_avg_of_min_max(values):
        print('before get_min')
        min_value = yield get_min(values)
        print('before get_max')
        max_value = yield get_max(values)
        print('before avg')
        avg = (min_value + max_value) / 2
        res.append(avg)

    @inline_callbacks
    def get_min(values):
        connection = yield connect('min_connection')
        return_value(min(values))

    @inline_callbacks
    def get_max(values):
        connection = yield connect('max_connection')
        return_value(max(values))

    loop.call_later(0, lambda: save_avg_of_min_max([11, 8, 10, 4]))
    loop.start()
    assert res == [7.5]
