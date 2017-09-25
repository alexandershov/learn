import pytest


DES = 0b110
TRES = 0b1110
QUATRO = 0b11110
INNER = 0b10


def my_decode_utf8(s):
    chars = []
    codepoint = 0
    n = 0
    for i, b in enumerate(s):
        if n == 0:
            if (b >> 3) == QUATRO:
                n = 3
                codepoint = 0b111 & b
            elif (b >> 4) == TRES:
                n = 2
                codepoint = 0b111_1 & b
            elif (b >> 5) == DES:
                n = 1
                codepoint = 0b111_11 & b
            elif b <= 127:
                codepoint = 0
                chars.append(chr(b))
            else:
                raise ValueError(i)
        else:
            assert n > 0
            assert (b >> 6) == INNER
            codepoint = (codepoint << 6) + (b & 0b111_111)
            n -= 1
            if not n:
                chars.append(chr(codepoint))
    return ''.join(chars)


def my_encode_utf8(s):
    result = []
    for c in s:
        n = ord(c)
        if n <= 127:
            result.append(n)
        elif n < 2 ** 11:
            result.append(0b1100_0000 | ((0b11111_000_000 & n) >> 6))  # top 5
            result.append(0b1000_0000 | (0b111_111 & n))    # next 6
        elif n < 2 ** 16:
            result.append(0b1110_0000 | ((0b1111_000000_000000 & n) >> 12))    # top 4
            result.append(0b1000_0000 | ((0b111111_000000 & n) >> 6))    # next 6
            result.append(0b1000_0000 | (0b111111 & n))    # next 6
        elif n < 2 ** 21:
            result.append(0b1111_0000 | ((0b111_000000_000000_000000 & n) >> 18))    # top 3
            result.append(0b1000_0000 | ((0b111111_000000_000000 & n) >> 12))    # next 6
            result.append(0b1000_0000 | ((0b111111_000000 & n) >> 6))    # next 6
            result.append(0b1000_0000 | (0b111111 & n))    # next 6
    return bytes(result)


@pytest.mark.parametrize('s', [
    (b'test'),
    ('привет'.encode('utf-8')),
    ('\u08ff'.encode('utf-8')),
    ('\U0001ffff'.encode('utf-8')),
])
def test_utf8(s):
    assert my_decode_utf8(s) == s.decode('utf-8')
    assert my_encode_utf8(my_decode_utf8(s)) == s

