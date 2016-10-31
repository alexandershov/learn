1. Hashtable.
2. BST.
3. Trie. Store pointers to next levels in linked list 
   to avoid always storing 10 pointers in an array. This solution saves
   memory but increases speed (we need to traverse a linked list).
   
We need about 33 bits to store one phone lg(10^10). Probably we can cut
global area code, and get to 29 bits (lg(10^9)). Then each node in a binary
tree is will take 32 * 3 (1value + 2pointers) bits == 96bits.
This means that to store 10,000 orders, we'll need to 960,000 bits,
in case of 16-bits pointers - 640,000 bits

What will hashtable take - depends on a load factor. Let's say we're using
robin hood hashing and load factor is 99%. This means that to store
10,000 orders we'll need 10101 * 16 bits = 161,000 bits

With trie, it's hard to tell. Let's say that we have 100 area codes. 
What, the hell just use a hashtable :)

I didn't counted storage of order data, basically it's another constant
to multiply.
