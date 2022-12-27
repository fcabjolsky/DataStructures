CFLAGS=-g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
MATHFLAG=-lm
VFLAGS=--track-origins=yes --leak-check=yes -s
OUTPUT_FILE=test_main

queue.o: ../queue.c ../queue.h
	gcc $(CFLAGS) -c ../queue.c 

testing.o: testing.c testing.h
	gcc $(CFLAGS) -c testing.c 

main_test.o: main_test.c 
	gcc $(CFLAGS) -c main_test.c

_test: main_test.o queue.o testing.o
	gcc main_test.o queue.o testing.o -o $(OUTPUT_FILE)

test: _test
	./$(OUTPUT_FILE)

valgrind_test: _test
	valgrind $(VFLAGS) ./$(OUTPUT_FILE)
	
clear:
	rm *.o