We can use another bitvector to store information about set bits.
Let's call this bitvector `y`. Let's call an original bitvector `x`.

Let's split bits of `x` into chunks of 16bits (or 8, whatever your want).
Then every time we're trying to set a bit from uninitialized block 
we initialize the whole block of this bit and then set.

Then every time we're trying to get a bit we have two cases:
* if it's from uninitialized block, then it's 0.
* otherwise just get it.

We're are using extra len(`x`)/8 bits of memory. And then, let's say
if we access only 1/10 of bit blocks, then
* we're avoiding setting 90% of blocks
* on each get/set we have one extra bitvector lookup.

