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

void free_array(int **array, size_t n) {
    for (size_t i = 0; i < n; i++) {
        free(array[i]);
    }
    free(array);
}

int **generate_array(size_t n) {
    int **test_array = malloc(sizeof(int *) * n);
    if (test_array == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < n; i ++) {
        int *value = malloc(sizeof(int));
        if (value == NULL) {
            free_array(test_array, i);
        }
        *value = (int)i;
        test_array[i] = value;
    }
    return test_array;
}

void testQueueStress() {
    print_header("Queue with lot of elements");

    size_t n = 10000;
    int **test_array = generate_array(n);
    queue_t *queue = queue_create();

    bool queued = true, first = true, polled = true, test_passed = true;
    //adding elements
    for (size_t i = 0; i < n; i++){
        queued = queue_add(queue, test_array[i]);
        first = queue_peek(queue) == test_array[0];
        if (!queued || !first){
            test_passed = false;
            break;
        }
    }
    print_test("elements added", test_passed);

    if (test_passed){
        size_t i = 0;
        while (!queue_is_empty(queue)){
            first = queue_peek(queue) == test_array[i];
            polled = queue_poll(queue) == test_array[i++];
            if (!first || ! polled){
                test_passed = false;
                break;
            }
        }
        print_test("polled elements", test_passed);

        if (test_passed){
            print_test("empty queue", queue_is_empty(queue));
            print_test("peek is NULL", queue_peek(queue) == NULL);
            print_test("poll is NULL", queue_poll(queue) == NULL);
        }
    }
    free_array(test_array, n);
    queue_destroy(queue, NULL);
}

void testQueueDynamicFree() {
    print_header("Queue dynamic free");
    size_t n = 10000;
    int **test_array = generate_array(n);
    queue_t *queue = queue_create();

    bool queued = true, first = true, test_passed = true;
    //adding elements
    for (size_t i = 0; i < n; i++){
        queued = queue_add(queue, test_array[i]);
        first = queue_peek(queue) == test_array[0];
        if (!queued || !first){
            test_passed = false;
            break;
        }
    }
    print_test("elements added", test_passed);
    free(test_array);
    queue_destroy(queue, free);
}

void testQueueAddNull() {
    print_header("Queue add NULL");

    queue_t* queue = queue_create();

    print_test("queue is empty", queue_is_empty(queue));
    print_test("add NULL", queue_add(queue, NULL));

    print_test("queue peek is NULL", queue_peek(queue) == NULL);
    print_test("queue is not empty", !queue_is_empty(queue));
    print_test("queue poll is NULL", queue_poll(queue) == NULL);
    print_test("queue is empty",queue_is_empty(queue));

    queue_destroy(queue, NULL);
}

void runTests() {
    testEmptyQueue();
    printf("\n");
    testQueueWithOneElement();
    printf("\n");
    testQueueStress();
    printf("\n");
    testQueueDynamicFree();
    printf("\n");
    testQueueAddNull();
}

int main() {
    runTests();
    // print_test("test testing framework", true);
    printf("Error count: %i\n", failure_count());
    return 0;
}