import asyncio
import logging
import os


def main():
    host = _get_env('NGL_HOST')
    port = int(_get_env('NGL_PORT'))
    _configure_logging()
    loop = asyncio.get_event_loop()
    loop.run_until_complete(check_nagle(
        loop=loop,
        host=host,
        port=port,
    ))
    loop.close()


def _configure_logging():
    logging.basicConfig(level=logging.INFO)


async def check_nagle(loop, host, port):
    logging.info('connecting to {}:{:d}'.format(host, port))
    all_words = [
        b'one', b'two', b'three', b'four', b'five',
        b'six', b'seven', b'eight', b'nine'
    ]
    reader, writer = await asyncio.open_connection(
        host=host,
        port=port,
        loop=loop,
    )
    for word in all_words:
        writer.write(word + b'\n')
    # to avoid sending FIN immediately
    await asyncio.sleep(1)
    writer.close()


def _get_env(name):
    value = os.getenv(name)
    if value is None:
        raise ValueError('unknown environment variable: {}'.format(name))
    return value


if __name__ == '__main__':
    main()
