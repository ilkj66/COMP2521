// Interface to the queue ADT

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef QUEUE_H
#define QUEUE_H

typedef int Item;

typedef struct queue *Queue;

/**
 * Creates a new empty queue
 */
Queue QueueNew(void);

/**
 * Frees all memory allocated to the queue
 */
void QueueFree(Queue q);

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it);

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q);

/**
 * Returns the number of items in the queue
 */
int QueueSize(Queue q);

/**
 * Returns whether the queue is empty or not
 */
bool QueueIsEmpty(Queue q);

/**
 * Returns the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueuePeek(Queue q);

#endif
