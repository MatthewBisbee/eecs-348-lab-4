CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2

.PHONY: all clean test

all: task1 task2

task1: task1.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

task2: task2.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS) -lm

test: all
	python3 tests/test_programs.py

clean:
	$(RM) task1 task2
