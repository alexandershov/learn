from twisted.internet.defer import inlineCallbacks
from twisted.internet.defer import returnValue
from twisted.internet.defer import Deferred
from twisted.internet import reactor


@inlineCallbacks
def my_tst():
    print('before yield')
    x = yield sleep(1)
    print('after yield')
    returnValue(x)


def sleep(n):
    task = Deferred()
    reactor.callLater(n, lambda: task.callback(None))
    return task
    

def main():
    reactor.callLater(1, lambda: my_tst())
    reactor.run()


if __name__ == '__main__':
    main()
