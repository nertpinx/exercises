#include <errno.h>
#include <stdlib.h>

/**
 * get_number: Convert const char * to long with error checking
 * @string: Input string to be converted
 * @value: Output value to be set
 *
 * Function converts @string into @value if and only if it is valid (meaning the
 * string contains only the valid number, no excess characters).
 *
 * Returns 0 in case of success, -1 otherwise. In case of an error it must not
 * touch the @value.
 */
int
get_number(const char *string,
           long *value)
{
}
