#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>

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
        fprintf(stdout, "queue is full : %d\n", di->q_head - di->q_tail);
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
        fprintf(stdout, "queue is empty : %d\n", di->q_head - di->q_tail);
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

void destroy_dish(struct dish *di)
{
    pthread_mutex_destroy(&di->q_lock);
    pthread_cond_destroy(&di->q_empty);
    pthread_cond_destroy(&di->q_full);
}

int get_dish_size(struct dish *di)
{
    int size = 0;
    (void) pthread_mutex_lock(&di->q_lock);
    size = di->q_head - di->q_tail;
    (void) pthread_mutex_unlock(&di->q_lock);

    return size;
}

void *consumer(void *thread_param)
{
    struct dish *di = (struct dish *) thread_param;
    struct entry e;

    while (1) {
        consume_entry(di, &e);
        fprintf(stdout, "current time is : %d\n", e.en);
    }
}

void *producer(void *thread_param)
{
    struct dish *di = (struct dish *) thread_param;
    struct entry *e = malloc(sizeof(struct entry));
    if (!e) {
        fprintf(stderr, "malloc memory fail\n");
    }

    while (1) {
        time_t t = time(NULL);
        e->en = t;
        produce_entry(di, e);
//        (void) pthread_mutex_lock(&di->q_lock);
//        fprintf(stdout, "current queue length is : %d\n", di->q_head - di->q_tail);
//        (void) pthread_mutex_unlock(&di->q_lock);
    }
    free(e);
}

void *show_dish_size(void *pthread_param)
{
    struct dish *di = (struct dish *) pthread_param;
    while (1) {
        fprintf(stdout, "current queue length is : %d\n", get_dish_size(di));
    }
}

int main(int argc, char *argv[])
{
    struct dish ent;
    pthread_t c_ptid, p_ptid, s_ptid;
    init_dish(&ent);

    fprintf(stdout, "start thread producer and consumer \n");
    pthread_create(&p_ptid, NULL, producer, &ent);
    pthread_create(&c_ptid, NULL, consumer, &ent);
    pthread_create(&s_ptid, NULL, show_dish_size, &ent);

    pthread_join(p_ptid, NULL);
    pthread_join(c_ptid, NULL);
    pthread_join(s_ptid, NULL);

}
