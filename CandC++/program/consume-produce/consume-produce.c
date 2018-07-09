#include <stdio.h>
#include <pthread.h>

#define Q_LENGTH 32
#define SIZEARRAY(e) Q_LENGTH

struct entry {
    int en;
};

struct dish {
    pthread_mutex_t q_lock;
    struct entry queue[Q_LENGTH];
    int q_head;
    int q_tail;
};

void init_dish(struct dish *di)
{
    pthread_mutex_init(&di->q_lock, NULL);

    di->q_head = di->q_tail = 0;
}

void produce_entry(struct dish *di, struct entry *e)
{
    pthread_mutex_lock(&di->q_lock);

    while (di->q_head - di->q_tail >= SIZEARRAY(di->queue)) {
        // queue is fulll
    }

    if (di->q_head - di->q_tail < SIZEARRAY(di-queue)) {
        di->queue[di->q_head % SIZEARRAY(di-queue)] = *e;
        di->q_head++;
    }

    pthread_mutex_unlock(&di->q_lock);
}

void consume_entry(struct dish *di, struct entry *e)
{
    pthread_mutex_lock(&di->q_lock);

    while (di->q_tail == di->q_head) {
        //queue is empty
    }

    if (di->q_tail < di->q_head) {
        *e = di->queue[di->q_tail % SIZEARRAY(di->queue)];
        di->q_tail++;

        if (di->q_tail >= SIZEARRAY(di->queue)) {
            di->q_tail -= SIZEARRAY(di->queue);
            di->q_head -= SIZEARRAY(di->queue);
        }
    }


    pthread_mutex_unlock(&di->q_lock);

}
