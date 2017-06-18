import heapq

class Task:
    def __init__(self):
        self._callbacks = []
    
    def add_callback(self, callback):
        self._callbacks.append(callback)

    def callback(self, value):
        for callback in self._callbacks:
            value = callback(value)
        return value


class EventLoop:
    def __init__(self):
        self._events = []
    
    def call_later(self, delay, fn):
        pass
    
    def start(self):
        pass

    
def test_task():
    values = []
    d = Task()
    d.add_callback(lambda v: values.append(v))
    assert d.callback(3) is None
    assert values == [3]


def test_event_loop():
    values = []
    loop = EventLoop()
    loop.call_later(1, lambda: values.append(3))
    loop.start()
    assert values == [3]
