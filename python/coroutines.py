import pytest


def twice(value, n):
    for _ in range(n):
        to_yield = value * 2
        try:
            value = yield to_yield
        except ValueError:
            value = 0
    return value + 1
    

def test_send():
    numbers = twice(9, 3)
    assert numbers.send(None) == 18
    assert numbers.send(4) == 8
    assert numbers.send(7) == 14
    with pytest.raises(StopIteration):
        numbers.send(9)


def test_throw():
    numbers = twice(9, 3)
    assert numbers.send(None) == 18
    # same as .send() but throws an exception instead
    assert numbers.throw(ValueError) == 0


def delegate_to(generator):
    x = yield from generator
    return x


def my_delegate_to(generator):
    value = None
    while True:
        try:
            to_yield = generator.send(value)
        except StopIteration as exc:
            x = exc.value
        else:
            value = yield to_yield


def test_yield_from():
    twice_gen = twice(6, 3)
    delegate_gen = delegate_to(twice_gen)
    assert delegate_gen.send(None) == 12
    assert delegate_gen.send(9) == 18
    assert delegate_gen.send(3) == 6
    try:
        delegate_gen.send(13)
    except StopIteration as exc:
        assert exc.value == 14
    else:
        assert False
