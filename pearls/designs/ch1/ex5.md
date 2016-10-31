We can store count in bit vector - each element will take 4 bits - to
2^4 > max_count. max_count == 10.
If we can have 4 times more memory, then it's fine.
Otherwise we can use multi-pass algorithm. Let's say we can have 2 times
more memory. Then bitvector can hold 2*max bits. Which means that including
counts it can hold counting info about max/2 bits.
Do it in two passes from [0, max/2), then [max/2, max). 

Then let's say we can't have more memory. In this case do it 4 passes.
First pass from [0, max/4), then [max/4, max/2), etc.
