## What is it?
Inefficient implementation of a bloom filter.

## What is a Bloom filter?
Bloom filter is a space efficient set that is sometimes wrong whether
some element is in it. 

The idea is the following: let's say you have a
bit array of length `n`. To add an element into Bloom filter convert
an element into `k` integers [0; n) and set corresponding bits to 1.

To test the presence of an element in a Bloom filter do the `k` dance
and check if every corresponding bit is equal 1. If it's not then an 
element is not in a filter. If it is equal to 1, then an element is 
_probably_ in a filter.
