#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "worker.h"

static void
perr(int error)
{
    errno = error;
    err(EXIT_FAILURE, NULL);
}

struct test_data {
    const char *name; /* Just so we don't have to format ti all the time */
    unsigned long number;
    unsigned long long expected_result;
};

#define test_start(str) printf("Testing '%s' ... ", str);
#define test_ok()       printf("[  \e[32mOK\e[0m  ]\n");
#define test_err(fmt, ...)                                    \
    do {                                                      \
        printf("[ \e[31mFAIL\e[0m ]\n");                      \
        printf("The test \e[31m" fmt "\e[0m\n", __VA_ARGS__); \
        ret = -1;                                             \
    } while (0)

#define DATA(x, y) { #x, (x), (y) }

/* This can be changed if you want to test with different number of threads. */
#define NUM_THREADS 10

static int
run_tests(unsigned int num_threads)
{
    /* Yeah, we can calculate them, but this is shorter */
    struct test_data data[] = {
        DATA(1, 2),
        DATA(2, 5),
        DATA(3, 10),
        DATA(4, 17),
        DATA(5, 28),
        DATA(6, 41),
        DATA(7, 58),
        DATA(8, 77),
        DATA(9, 100),
        DATA(10, 129),
        DATA(100, 24133),
        DATA(110, 29897),
        DATA(120, 36227),
        DATA(130, 43201),
        DATA(140, 50887),
        DATA(150, 59269),
        DATA(160, 68341),
        DATA(170, 78149),
        DATA(180, 88585),
        DATA(190, 99685),
        DATA(200, 111587),
        /* Feel free to add more tests below this line. */
    };
    size_t ndata = sizeof(data) / sizeof(*data);
    size_t i = 0;
    int ret = 0;

    for (i = 0; i < ndata; i++) {
        /* TODO: allocate only what's needed */
        pthread_t thread_ids[NUM_THREADS] = {0};
        struct worker_data *worker_data = NULL;
        unsigned long long actual_result = 0;
        size_t j = 0;
        int rv = 0;

        test_start(data[i].name);

        worker_data = worker_data_init(data[i].number);
        if (!worker_data)
            err(EXIT_FAILURE, NULL);

        for (j = 0; j < num_threads; j++) {
            rv = pthread_create(thread_ids + j, NULL, worker_func, worker_data);
            if (rv)
                perr(rv);
        }

        for (j = 0; j < num_threads; j++) {
            rv = pthread_join(thread_ids[j], NULL);
            if (rv)
                perr(rv);
        }

        actual_result = worker_data_cleanup_get_result(worker_data);

        if (actual_result == data[i].expected_result) {
            test_ok();
        } else {
            test_err("calculated %llu instead of %llu",
                     actual_result,
                     data[i].expected_result);
        }
    }

    return ret;
}

int
main(int argc __attribute__((unused)),
     char **argv __attribute__((unused)))
{
    printf("Starting tests single-threaded\n");

    if (run_tests(1) < 0) {
        printf("First fix the single-threaded one and then you can move on\n");
        return EXIT_FAILURE;
    }

    printf("Starting tests multi-threaded using %d threads\n", NUM_THREADS);

    if (run_tests(NUM_THREADS) < 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
