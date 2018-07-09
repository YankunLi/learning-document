#include <stdio.h>
#include <pthread.h>

#define Q_LENGTH 32
#define SIZEARRAY(e) (sizeof(e) / sizeof(e[0]))

struct entry {
    int en;
};

struct dish {
    pthread_mutex_t q_lock;
//    pthread_mutex_t q_cond;
    pthread_cond_t q_full;
    pthread_cond_t q_empty;
    struct entry queue[Q_LENGTH];
    int q_head;
    int q_tail;
};

void init_dish(struct dish *di)
{
    int ok;
    ok = 0 == pthread_mutex_init(&di->q_lock, NULL);
//    ok &= 0 == pthread_mutex_init(&di->q_cond, NULL);
    ok &= 0 == pthread_cond_init(&di->q_full, NULL);
    ok &= 0 == pthread_cond_init(&di->q_empty, NULL);
    if (!ok) {

    }

    di->q_head = di->q_tail = 0;
}

void produce_entry(struct dish *di, struct entry *e)
{
    (void) pthread_mutex_lock(&di->q_lock);

    while (di->q_head - di->q_tail >= SIZEARRAY(di->queue)) {
        // queue is fulll
        (void) pthread_cond_wait(&di->q_full, &di->q_lock);
    }

    if (di->q_head - di->q_tail < SIZEARRAY(di->queue)) {
        di->queue[di->q_head % SIZEARRAY(di->queue)] = *e;
        di->q_head++;
    }

    (void) pthread_cond_signal(&di->q_empty);
    (void) pthread_mutex_unlock(&di->q_lock);
}

void consume_entry(struct dish *di, struct entry *e)
{
    (void) pthread_mutex_lock(&di->q_lock);

    while (di->q_tail == di->q_head) {
        //queue is empty
        pthread_cond_wait(&di->q_empty, &di->q_lock);
    }

    if (di->q_tail < di->q_head) {
        *e = di->queue[di->q_tail % SIZEARRAY(di->queue)];
        di->q_tail++;

        if (di->q_tail >= SIZEARRAY(di->queue)) {
            di->q_tail -= SIZEARRAY(di->queue);
            di->q_head -= SIZEARRAY(di->queue);
        }
    }

    (void) pthread_cond_signal(&di->q_full);
    (void) pthread_mutex_unlock(&di->q_lock);

}
