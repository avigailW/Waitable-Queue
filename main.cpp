#include <iostream>
#include <unistd.h>
#include "BufferQueue.h"
#include "Producer.h"
#include "Consumer.h"

#define CONSUMER_AMOUNT 4
#define PRODUCER_AMOUNT 3

void testProducerConsumer()
{
    BufferQueue bufferQueue;
    Producer *producers;
    Consumer *consumers;

    for (int i = 0; i < PRODUCER_AMOUNT; ++i)
    {
        producers[i] = Producer(i, &bufferQueue);
        producers[i].StartProducing();
    }
    for (int i = 0; i < CONSUMER_AMOUNT; ++i)
    {
        consumers[i] = Consumer(i, &bufferQueue);
        consumers[i].StartConsuming();
    }


    for (int i = 0; i < 10; ++i)
        sleep(1);


    for (int i = 0; i < PRODUCER_AMOUNT; i++)
    {
        producers[i].StopProducing();
    }
    for (int i = 0; i < CONSUMER_AMOUNT; i++)
    {
        consumers[i].StopConsuming();
    }

}

int main()
{
    int val = 0;
    testProducerConsumer();
    printf("\n\n------------\n\nFinished test");
    return 0;
}