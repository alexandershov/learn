from bloomfilter import BloomFilter


def test_added_is_present():
    bloom_filter = BloomFilter(num_bits=1000, num_hashes=2)
    obj = 'x'
    assert obj not in bloom_filter
    bloom_filter.add(obj)
    assert obj in bloom_filter
