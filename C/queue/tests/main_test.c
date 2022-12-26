#include "testing.h"
#include "../queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void testEmptyQueue() {
    print_header("Empty queue\n");
    queue_t* queue = queue_create();
    print_test("queue is not NULL", queue != NULL);
    print_test("queue is empty", queue_is_empty(queue));
    print_test("queue peek is NULL", queue_peek(queue) == NULL);
    print_test("queue poll is NULL", queue_poll(queue) == NULL);
    queue_destroy(queue, NULL);
}

void testQueueWithOneElement() {
    print_header("Queue With One Element\n");
    queue_t *queue = queue_create();
    print_test("queue is not NULL", queue != NULL);
    int testValueTwo = 2;
    print_test("queue add number 2: ", queue_add(queue, &testValueTwo));
    print_test("queue is not empty", !queue_is_empty(queue));
    print_test("queue peek is 2", queue_peek(queue) == &testValueTwo);
    print_test("queue poll is 2", queue_poll(queue) == &testValueTwo);
    print_test("queue is empty", queue_is_empty(queue));
    print_test("queue peek is NULL", queue_peek(queue) == NULL);
    print_test("queue poll is NULL", queue_poll(queue) == NULL);
    queue_destroy(queue, NULL);
}

void runTests() {
    testEmptyQueue();
    printf("\n");
    testQueueWithOneElement();
    printf("\n");
}

int main() {
    runTests();
    // print_test("test testing framework", true);
    printf("Error count: %i\n", failure_count());
    return 0;
}