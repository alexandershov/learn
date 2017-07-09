import datetime as dt
import logging
import random
import time


def _random_soon():
    now = dt.datetime.utcnow()
    seconds = random.random()
    return now + dt.timedelta(seconds=seconds)


class _AsyncConnection:
    def __init__(self):
        self.ready_at = _random_soon()

    @property
    def is_ready(self):
        return dt.datetime.utcnow() >= self.ready_at

class _AsyncSocket:
    COUNTER = 0
    def __init__(self):
        _AsyncSocket.COUNTER += 1
        self._num = _AsyncSocket.COUNTER

    def read(self, max_value):
        return _AsyncRead(max_value)

    def __str__(self):
        return f'_AsyncSocket({self._num})'


class _AsyncRead:
    def __init__(self, max_value):
        self.max_value = max_value
        self.ready_at = _random_soon()

    @property
    def is_ready(self):
        return dt.datetime.utcnow() >= self.ready_at


class EventLoop:
    def __init__(self):
        self._coroutines = {}

    def run_until_complete(self, main_coroutine):
        self.run(main_coroutine)
        while True:
            for coroutine, value in list(self._get_ready_values()):
                try:
                    self.run(coroutine, value)
                except StopIteration as exc:
                    logging.info('coroutine %s returned value %s', coroutine, exc.value)
                    del self._coroutines[coroutine]
                    if coroutine is main_coroutine:
                        return exc.value
            
    def run(self, coroutine, value=None):
        obj = coroutine.send(value)
        self._coroutines[coroutine] = obj

    def _get_ready_values(self):
        for coroutine, value in self._coroutines.items():
            if isinstance(value, _AsyncConnection):
                if value.is_ready:
                    yield coroutine, _AsyncSocket()
            elif isinstance(value, _AsyncRead):
                if value.is_ready:
                    yield coroutine, random.randint(1, value.max_value)
            else:
                yield coroutine, value


def serve(event_loop):
    for _ in range(10):
        socket = yield from accept()
        logging.info('accepted connection from socket %s', socket)
        event_loop.run(get_ratio(socket))
    return 'done'


def main():
    _setup_logging()
    event_loop = EventLoop()
    value = event_loop.run_until_complete(serve(event_loop))
    logging.info('finished event_loop with value %s', value)


def get_first_number():
    t = yield 4
    socket = yield from connect()
    logging.info('connected to socket %s', socket)
    x = yield socket.read(30)
    return x


def get_second_number():
    socket = yield from connect()
    logging.info('connected to socket %s', socket)
    x = yield socket.read(300)
    return x


def connect():
    socket = yield _AsyncConnection()
    return socket


def accept():
    socket = yield _AsyncConnection()
    return socket


def get_ratio(socket):
    logging.info('starting to get ratio of socket %s', socket)
    x = yield from get_first_number()
    logging.info('first number is %s', x)
    y = yield from get_second_number()
    logging.info('second number is %s', y)
    return x / y


def _setup_logging():
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s %(levelname)s %(message)s')


if __name__ == '__main__':
    main()
