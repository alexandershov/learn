from collections import OrderedDict
import asyncio
import logging
import os
import time

import matplotlib.pyplot as plt

MAX_BYTES = 1 * 1024 * 1024  # 1 megabyte
CHUNK_SIZE = 1024  # 1 kilobyte


def main():
    host = _get_env('TSS_HOST')
    port = int(_get_env('TSS_PORT'))
    _configure_logging()
    loop = asyncio.get_event_loop()
    downloader = Downloader(
        loop=loop,
        host=host,
        port=port,
    )
    loop.run_until_complete(downloader.download())
    loop.close()


def _configure_logging():
    logging.basicConfig(level=logging.INFO)


class Downloader:
    def __init__(self, loop, host, port):
        self.loop = loop
        self.host = host
        self.port = port
        self.num_bytes = 0
        self.stats = OrderedDict()  # time -> speed
        self.polling_interval = 0.01
        self.started_at = None

    async def download(self):
        reader, writer = await asyncio.open_connection(
            host=self.host,
            port=self.port,
            loop=self.loop,
        )
        self.started_at = time.time()
        self.loop.call_soon(self.save_stats)
        while self.num_bytes < MAX_BYTES:
            data = await reader.read(CHUNK_SIZE)
            self.num_bytes += len(data)
        self.plot_stats()

    def save_stats(self):
        duration = time.time() - self.started_at
        self.stats[duration] = self.num_bytes / duration
        self.loop.call_later(self.polling_interval, self.save_stats)

    def plot_stats(self):
        plt.plot(list(self.stats.keys()), list(self.stats.values()))
        plt.xlabel('time (seconds)')
        plt.ylabel('speed (bytes/second)')
        plt.show()


def _get_env(name):
    value = os.getenv(name)
    if value is None:
        raise ValueError('unknown environment variable: {}'.format(name))
    return value


if __name__ == '__main__':
    main()
