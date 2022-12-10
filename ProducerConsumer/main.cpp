/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author ??? (TODO: your name)
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

// global buffer object
Buffer buffer;

pthread_mutex_t _mutex;	
sem_t _full;				
sem_t _empty;			

// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);
    // buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        // TODO: Add synchronization code here
        sem_wait(&_empty); // Wait for an empty slot
        pthread_mutex_lock(&_mutex); // Lock the buffer
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
        pthread_mutex_unlock(&_mutex); // Release the buffer lock
        sem_post(&_full); // Signal that the buffer is full
    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        // TODO: Add synchronization code here
        sem_wait(&_full); // Semaphore wait
        pthread_mutex_lock(&_mutex); // Mutex lock
        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }

        pthread_mutex_unlock(&_mutex); // Unlock the mutex since the critical section is done
        sem_post(&_empty); // Notify the semaphore that the buffer is not full
    }
}

int main(int argc, char *argv[]) {
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    /* TODO: 2. Initialize buffer and synchronization primitives */
    /* TODO: 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    /* TODO: 4. Create consumer thread(s) */
    /* TODO: 5. Main thread sleep */
    /* TODO: 6. Exit */
  srand(time(NULL));
  if (argc != 4) {
    cout << "Expected 3 arguments, received" << argc - 1 << endl;
    return 1;
  }
  
  // TODO: 1. Get command line arguments argv[1],argv[2],argv[3] 
  int sleepTime = atoi(argv[1]);
  int producers = atoi(argv[2]);
  int consumers = atoi(argv[3]);
  
  // TODO: 2. Initialize buffer and synchronization primitives
  pthread_mutex_init(&_mutex, NULL);
  sem_init(&_empty, 0, 5);
  cout << "Initialized empty semaphore" << endl;
  sem_init(&_full, 0, 0);
  cout << "Initialized full semaphore" << endl;

  pthread_t producerThreads[producers];
  pthread_t consumerThreads[consumers];

  // TODO: 3. Create producer thread(s).
  for (int i = 0; i < producers; i++) {
    // Create a thread and pass the thread ID as the parameter
    // pthread_create(&producerThreads[i], NULL, &producer, NULL);
    pthread_create(&producerThreads[i], NULL, &producer, (void *) &i);
  }
  
  // TODO: 4. Create consumer thread(s).
  for (int i = 0; i < consumers; i++) {
    pthread_create(&consumerThreads[i], NULL, &consumer, NULL);
  }

  /* TODO: 5. Main thread sleep */
  sleep(sleepTime);
  
  /* TODO: 6. Exit */
  return 0;
}
