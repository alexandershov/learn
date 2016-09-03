## What is it?

Some code to check that Nagle algorithm exists and can be disabled with
TCP_NODELAY.

## How to run it?
```shell
$ nc -l 1234
```

On local host run:

```shell
$ NGL_HOST=remote_host NGL_PORT=1234 NGL_TCP_NODELAY=1 python client.py
```

and look at wireshark/tcpdump for `host remote_host and port 1234`

## Notes
