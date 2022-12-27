#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

// node definiton
typedef struct node {
    void* data;
    struct node* next;
} node_t;

// queue definition
struct queue {
    node_t* first;
    node_t* last;
};

/**
 * Auxiliary function to create a new node
 * Return a new node with the data and next pointing to the
 * next node or NULL
*/
node_t *_node_create(void *data, node_t *next) {
    node_t* node = malloc(sizeof(node_t));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = next;
    return node;
}

/**
 * Auxiliary function to destroy a node
 * if destroy_data is valid. It destroys the data
*/
void _node_destroy(node_t *node, void (*destroy_data)(void *)) {
    if (destroy_data != NULL) {
        destroy_data(node->data);
    }
    free(node);
}

queue_t *queue_create(void) {
    queue_t *queue = malloc(sizeof(queue_t));
    if (queue == NULL) {
        return NULL;
    }
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}


void queue_destroy(queue_t *queue, void (*destroy_data)(void *)) {
    while (!queue_is_empty(queue)) {
        void * data = queue_poll(queue);
        if (destroy_data != NULL) {
            destroy_data(data);
        }
    }
    free(queue);
}


bool queue_is_empty(const queue_t *queue) {
    return queue != NULL ? queue->first == NULL : true;
}

bool queue_add(queue_t *queue, void *data) {
    if (queue == NULL) {
        return false;
    }
    node_t *node = _node_create(data, NULL);
    if (node == NULL) {
        return false;
    }

    if (queue_is_empty(queue)) {
        queue->first = node;
    } else {
        queue->last->next = node;
    }
    queue->last = node;
    return true;
}

void *queue_peek(const queue_t *queue) {
    return queue_is_empty(queue) ? NULL : queue->first->data;
}

void *queue_poll(queue_t *queue) {
    if (queue_is_empty(queue)) {
        return NULL;
    }
    node_t *node = queue->first;
    queue->first = node->next;
    void *data = node->data;
    _node_destroy(node, NULL);
    return data;
}
