
#ifndef PRODECER_CONSUMER_C___PRODUCER_H
#define PRODECER_CONSUMER_C___PRODUCER_H

#include "BufferQueue.h"
#include <stdio.h>
#include <stdlib.h>

#define PRODUCER_PRODUCTS 40

class Producer {
public:

    Producer(int unique_id, BufferQueue *bQueue)
    {
        m_uniqueid = unique_id;
        m_bufferQueue = bQueue;
        m_count = 0;
    }

    ~Producer()
    {

    }

    void StartProducing()
    {
        sentinal = true;
        m_count = 0;
        pthread_create(&m_thread, NULL, addProduct, this);
    }

    void StopProducing()
    {
        sentinal = false;
        void* ret_val;
        pthread_join(m_thread, &ret_val);
    }

private:
    static void* addProduct(void* param)
    {
        Producer* _this = (Producer*) param;
        while(_this->sentinal && _this->m_count < PRODUCER_PRODUCTS)
        {
            _this->my_created_product = rand() % NUM_SIZE;
            _this->m_bufferQueue->addProductToQueue(_this->my_created_product);
            printf("Producer %d created product %d\n ", _this->m_uniqueid, _this->my_created_product);
            ++(_this->m_count);
        }

        return NULL;
    }
    bool sentinal;
    BufferQueue *m_bufferQueue;
    pthread_t m_thread;
    int my_created_product;
    int m_uniqueid;
    int m_count;
};



#endif