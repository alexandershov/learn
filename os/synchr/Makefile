futex:
	clang++ -std=c++14 -o futex_mutex -lpthread futex_mutex.cpp && ./futex_mutex 2>&1 | ./analyze.py

condvar:
	clang++ -std=c++14 -o condvar -lpthread condvar.cpp && ./condvar


.PHONY: futex condvar
