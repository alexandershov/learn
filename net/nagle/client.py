import asyncio
import logging
import os
import socket

def main():
    host = _get_env('NGL_HOST')
    port = int(_get_env('NGL_PORT'))
    use_tcp_nodelay = bool(int(_get_env('NGL_TCP_NODELAY', 0)))
    _configure_logging()
    loop = asyncio.get_event_loop()
    loop.run_until_complete(check_nagle(
        loop=loop,
        host=host,
        port=port,
        use_tcp_nodelay=use_tcp_nodelay,
    ))
    loop.close()


def _configure_logging():
    logging.basicConfig(level=logging.INFO)


async def check_nagle(loop, host, port, use_tcp_nodelay):
    logging.info('connecting to {}:{:d}, TCP_NODELAY={}'.format(host, port, use_tcp_nodelay))
    all_words = [
        b'one', b'two', b'three', b'four', b'five',
        b'six', b'seven', b'eight', b'nine'
    ]
    reader, writer = await asyncio.open_connection(
        host=host,
        port=port,
        loop=loop,
    )
    if use_tcp_nodelay:
        _set_tcp_nodelay(writer)

    for word in all_words:
        writer.write(word + b'\n')
    # to avoid sending FIN immediately
    await asyncio.sleep(1)
    writer.close()


def _set_tcp_nodelay(writer):
    logging.info('setting TCP_NODELAY')
    socket_obj = writer.get_extra_info('socket')
    socket_obj.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)


def _get_env(name, default=None):
    value = os.getenv(name, default)
    if value is None:
        raise ValueError('unknown environment variable: {}'.format(name))
    return value


if __name__ == '__main__':
    main()
