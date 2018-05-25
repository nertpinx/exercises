#include "worker.h"

#include <errno.h>
#include <stdlib.h>

#include "primes.h"

struct worker_data {
    /* Feel free to modify the internals of this function as needed. */
    unsigned long number;  /* number of primes to be summed up */
    unsigned long long result;
    unsigned long current;
};

/**
 * worker_data_init: Initializes data for the workers
 * @number: Number of primes to be summed up
 *
 * Function allocates and initializes the internal structure that keeps all the
 * needed data in itself.  This struct will be passed to all the workers as the
 * opaque pointer.  It can do any allocations and setting up that's needed.
 *
 * Returns pointer to the new structure.  In case of an error, the function
 * returns NULL and sets errno appropriately.
 */
struct worker_data *
worker_data_init(unsigned long number)
{
    struct worker_data *ret = calloc(1, sizeof(*ret));

    if (ret)
        ret->number = number;

    return ret;
}

/**
 * worker_data_cleanup_get_result: Clean-up worker data and get the final result
 * @worker_data: Pointer to the struct to be freed
 *
 * Function cleans up all the data allocated in worker_data_init() and extracts
 * the result of the operations done by all threads.
 *
 * Returns the result of the operation.
 */
unsigned long long
worker_data_cleanup_get_result(struct worker_data *worker_data)
{
    unsigned long long ret = worker_data->result;

    free(worker_data);

    return ret;
}

/**
 * worker_func: Entry point of each thread
 * @opaque: Pointer to initialized worker_data struct
 *
 * Function converts @string into @value if and only if it is valid (meaning the
 * string contains only the valid number, no excess characters).  This function
 * must be thread-safe as it will be called from multiple threads
 * simultaneously.
 *
 * Returns NULL.
 */
void *
worker_func(void *opaque)
{
    struct worker_data *data = opaque;

    /* This function is wrong (and it should be obvious why).  Fix it up so that
     * it works properly without race conditions and all the workers work in
     * parallel.
     */
    while (data->current < data->number) {
        unsigned long nth_prime = prime_get_nth(data->current);

        if (!nth_prime)
            return NULL;

        data->current++;
        data->result += nth_prime;
    }

    return NULL;
}
