#ifndef __WORKER_H__
# define __WORKER_H__

struct worker_data;

struct worker_data *
worker_data_init(unsigned long number);

unsigned long long
worker_data_cleanup_get_result(struct worker_data *worker_data);

void *
worker_func(void *opaque);

#endif /* __WORKER_H__ */
