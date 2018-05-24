PROGRAMS = thread_sync

thread_sync_SOURCES = thread_sync.c worker.c worker.h primes.c primes.h
thread_sync_LIBS = pthread

# Thanks to -O0 we don't need to have that many threads to run into the wanted
# race condition
CFLAGS = -O0 -ggdb -std=gnu11 -Wall -Wextra -Wmissing-declarations -Werror

include ../Makefile.inc
