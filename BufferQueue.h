

#ifndef PRODECER_CONSUMER_C___BUFFERQUEUE_H
#define PRODECER_CONSUMER_C___BUFFERQUEUE_H

#include <pthread.h>
#define NUM_SIZE 1000000
#define BUFFER_SIZE 6

class BufferQueue {

public:
    void addProductToQueue(int product);
    int consumeFromQueue();
    BufferQueue();
    ~BufferQueue();

private:
    int in;
    int out;
    int m_buffer[BUFFER_SIZE];
    pthread_mutex_t m_lock;


};

inline BufferQueue::BufferQueue() {
    pthread_mutex_init(&m_lock, NULL);
    in = 0;
    out = 0;
}

inline BufferQueue::~BufferQueue() {
    pthread_mutex_destroy(&m_lock);
}

inline void BufferQueue::addProductToQueue(int product) {


    pthread_mutex_lock(&m_lock);
    if (((in + 1) % BUFFER_SIZE) != out)/* do nothing */
    {
        //printf("thread id: %d - product %d producing %d\n", pid, in, product);
        m_buffer[in] = product;
        in = (in + 1) % BUFFER_SIZE;
    }
    pthread_mutex_unlock(&m_lock);

}

inline int BufferQueue::consumeFromQueue() {
    int next_consumed;
    pthread_mutex_lock(&m_lock);
    if (in != out) /* do nothing */
    {
        next_consumed = m_buffer[out];
        //printf("thread id: %d - consumer %d consuming %d\n", pid, out, next_consumed.num);
        out = (out + 1) % BUFFER_SIZE;
        /* consume the item in next consumed */

    }
    pthread_mutex_unlock(&m_lock);
    return next_consumed;

}

#endif