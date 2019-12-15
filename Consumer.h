
#ifndef PRODECER_CONSUMER_C___CONSUMER_H
#define PRODECER_CONSUMER_C___CONSUMER_H

#include "BufferQueue.h"
#include <stdio.h>

#define CONSUMER_PRODUCTS 30

class Consumer {

    public:
    Consumer(int unique_id, BufferQueue *bQueue);
    void StartConsuming();
    void StopConsuming();

private:
        static void* consumeProduct(void* param);

        bool sentinal;
        BufferQueue *m_bufferQueue;
        pthread_t thread;
        int my_consumed_product;
        int m_uniqueid;
        int m_count;

};


inline Consumer::Consumer(int unique_id, BufferQueue *bQueue)
{
    m_uniqueid = unique_id;
    m_bufferQueue = bQueue;
    m_count = 0;
}


inline void Consumer::StartConsuming()
{
    sentinal = true;
    pthread_create(&thread, NULL, consumeProduct, this);
}

inline void Consumer::StopConsuming()
{
    sentinal = false;
    void* ret_val;
    pthread_join(thread, &ret_val);
}

inline void* Consumer::consumeProduct(void* param)
{
    Consumer* _this = (Consumer*) param;
    while(_this->sentinal && _this->m_count < CONSUMER_PRODUCTS)
    {
        _this->my_consumed_product = _this->m_bufferQueue->consumeFromQueue();
        printf("Consumer %d consumed product %d\n ", _this->m_uniqueid, _this->my_consumed_product);
    }

    return NULL;
}

#endif