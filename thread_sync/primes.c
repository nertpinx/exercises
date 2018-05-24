#include "primes.h"

#include <errno.h>
#include <limits.h>
#include <stddef.h>

/**
 * prime_get_nth: Get @n-th prime
 * @n: Index of the prime to be returned
 *
 * Function calculates @n-th prime counted from 0.  So 0th prime is 2, 1st one
 * is 3 and so on.
 *
 * Returns the calculated prime.  In case of an error, the function returns 0
 * and sets errno appropriately.
 */
unsigned long
prime_get_nth(unsigned long n)
{
    size_t i;

    /* The dumbest and possibly grossest way to calculate primes with even
     * dumber overflow protection. */
    n++;

    for (i = 2; n && i >= 2; i++) {
        size_t j;

        for (j = 2; j < i; j++) {
            if (i % j == 0)
                break;
        }

        if (i == j && !--n)
            break;
    }

    if (i < 2 || i > ULONG_MAX) {
        errno = ERANGE;
        return 0;
    }

    return i;
}
