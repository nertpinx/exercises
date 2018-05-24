
struct worker_data;

struct worker_data *
worker_data_init(unsigned long number);

unsigned long long
worker_data_cleanup_get_result(struct worker_data *worker_data);

void *
worker_func(void *opaque);
