import os


def main():
    host = _get_env('TSS_HOST')
    port = int(_get_env('TSS_PORT'))
    print(host, port)


def _get_env(name):
    value = os.getenv(name)
    if value is None:
        raise ValueError('unknown environment variable: {}'.format(name))
    return value


if __name__ == '__main__':
    main()
