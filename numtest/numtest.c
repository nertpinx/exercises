#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "getnum.h"

struct test_data {
    const char *string;
    long number;
    bool fail;
};

#define test_start(str) printf("Testing '%s' ... ", str);
#define test_ok()       printf("[  \e[32mOK\e[0m  ]\n");
#define test_err(fmt, ...)                                    \
    do {                                                      \
        printf("[ \e[31mFAIL\e[0m ]\n");                      \
        printf("The test \e[31m" fmt "\e[0m\n", __VA_ARGS__); \
        ret = EXIT_FAILURE;                                   \
        continue;                                             \
    } while (0)

#define DATA(x)      { #x, x, false }
#define DATA_FAIL(x) { x, .fail = true }

int
main(int argc __attribute__((unused)),
     char **argv __attribute__((unused)))
{
    struct test_data data[] = {
        DATA(-90909),
        DATA(-1),
        DATA(0),
        DATA(123),
        DATA(0x123),
        DATA(-0777),
        DATA_FAIL(""),
        DATA_FAIL("blah"),
        DATA_FAIL("987muhehehe"),
        DATA_FAIL("1234567890123456789012345678901234567890"),
        /* Feel free to add more tests below this line. */
    };
    size_t ndata = sizeof(data) / sizeof(*data);
    size_t i = 0;
    int ret = EXIT_SUCCESS;

    srand(time(NULL));

    for (i = 0; i < ndata; i++) {
        long temp = rand();
        long value = temp;
        int ret;

        test_start(data[i].string);

        ret = get_number(data[i].string, &value);

        if (ret < 0) {
            if (!data[i].fail)
                test_err("should not fail, but returned %d", ret);
            else if (temp != value)
                test_err("should not changed the value to '%ld' when failing",
                         value);
            else
                test_ok();
        } else if (data[i].fail) {
            test_err("should have failed, but instead returned '%d' "
                     "and converted the string to '%ld'",
                     ret, value);
        } else if (data[i].number != value) {
            test_err("should set value to '%ld', "
                     "but instead converted it to '%ld'",
                     data[i].number, value);
        } else {
            test_ok();
        }
    }

    return ret;
}
