#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/**
 * Data type defintion *
 * This queue is a generic pointer implementation.
*/
struct queue;
typedef struct  queue queue_t;

/**
 * METHODS
*/

/**
 * Creates a new queue.
 * Returns an empty queue or NULL in case of error
 * O(1)
*/
queue_t *queue_create(void);

/**
 * Destroys the queue. If destroy_data is valid, it calls the function for
 * each element in the queue.
 * O(n) -> needs to destroy each element
*/
void queue_destroy(queue_t *queue, void (*destroy_data)(void *));

/**
 * return true if the queue has any element, otherwise it returns false
 * O(1)
*/
bool queue_is_empty(const queue_t *queue);

/**
 * Adds an element in the queue. Return false in case of error
 * O(1)
*/
bool queue_add(queue_t *queue, void *data);

/**
 * Retrieves, but doesn't remove the head of the queue. Returns NULL if 
 * the queue is empty 
 * O(1)
*/
void *queue_peek(const queue_t *queue);

/**
 * Retrieves and remove the head of the queue. Returns NULL if the queue is
 * empty.
 * O(1)
*/
void *queue_poll(queue_t *queue);

#endif