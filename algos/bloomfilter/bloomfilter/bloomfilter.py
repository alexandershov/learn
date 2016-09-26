class BloomFilter(object):
    def __init__(self, num_bits, num_hashes):
        self._num_hashes = num_hashes
        # okay, we should use real bit array here, but for simplicity let's use a list
        self._bit_array = [0] * num_bits

    def add(self, item):
        bits = self._get_bits(item)
        for i in bits:
            self._bit_array[i] = 1

    def __contains__(self, item):
        bits = self._get_bits(item)
        return all(self._bit_array[i] == 1 for i in bits)

    def _get_bits(self, item):
        hashes = [
            hash((i, item))
            for i in range(self._num_hashes)
        ]
        bits = [
            abs(one_hash) % self._num_hashes
            for one_hash in hashes
        ]
        return bits
