#!/usr/bin/env python3.6

import argparse
import collections
import itertools


def main():
    args = _parse_args()
    numbers = _get_all_thread_numbers(args.fileobj)
    for x, y in _get_pairs(numbers):
        if x != y:
            print(f'{x} is followed by {y}')
    counter = collections.Counter(numbers)
    for n, count in counter.items():
        if count != 2:
            print(f'{n} has count {count}')
    print(f'got {len(numbers)} lines')


def _parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('fileobj', type=argparse.FileType('r'), default='-', nargs='?')
    return parser.parse_args()


def _get_all_thread_numbers(fileobj):
    result = []
    for line in fileobj:
        line = line.strip()
        if line.startswith('thread'):
            result.append(_get_thread_number(line))
    return result


def _get_pairs(seq):
    even = seq[::2]
    odd = seq[1::2]
    return itertools.zip_longest(even, odd)
    

def _get_thread_number(line):
    return int(line.split()[1])


if __name__ == '__main__':
    main()
