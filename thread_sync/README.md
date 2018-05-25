# Make threads synchronized

In file `worker.c` fix function `worker_func()` so that it properly synchronizes
in case the program runs multithreaded.  You can modify `struct worker_data` and
bodies for all functions in `worker.c`.  Make sure you clean up after yourself
so that there are no leaks.

Hints:
- If you grab a lock at the top fo `worker_func()` and release it at the end,
  then the tests will pass, but the solution is wrong, because all the work is
  done by a single thread.  If you have an idea how to test this easily without
  over-complicating the code, then feel free to submit a PR.
- No need to keep everything under one mutex, but more than two is too much.
- Even with one mutex, it can be done almost as efficiently as with two of them
  (it would probably boil down to how efficient the mutex implemetation is).

Bonuses:
- The initial implementation doesn't error out in case there is an error in any
  worker thread.  Fix that.
- The prime calculation is very, very dumb.  Fix `prime_get_nth` so that it uses [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).
- Even with the above point, the calculation is still slow.  Fix it up so that
  the sieve is shared between all worker threads.
