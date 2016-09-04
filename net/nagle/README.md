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
Nagle algorithm is: if there's some unacked packets and current packet
size is less than MTU, then don't send new packet immediately. Wait for
an ACK or wait for more data.

This behaviour can be switched off with TCP_NODELAY flag. In this case
we'll send new data as soon as possible.

## Lessons learned
I've spent a lot of time creating sockets with TCP_NODELAY and still
having Nagle on. The reason was simple - I set TCP_NODELAY inside of
the Docker container and Mac OS X was completely unaware of it.
