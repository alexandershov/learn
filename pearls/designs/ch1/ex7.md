We can store sit counts as an array of 16-bit integers. Actually we need
10 bits to represent all numbers from 0 to 999.

courses[i] = n, which means that course `i` has n seats left.
The memory cost is 10000 * 16bit = 160000bits = 20KB. We have 10KB left.
Yay!

The runtime efficiency is pretty good, course lookup is just a vector
lookup O(1), so overall efficiency is O(num_requests) = O(80000)
