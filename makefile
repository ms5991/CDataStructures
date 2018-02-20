LIST_HEADER = ./list/list.h
TEST_HEADERS = ./tests/list_test.h

default: structures

all: default

list.o: ./list/list.c $(LIST_HEADER)
	gcc -c -o list.o

structures: list.o
	gcc list.o -o structures

test: structures main.c $(TEST_HEADERS)
	gcc structures main.c -o test

clean:
	-rm -f structures
	-rm -f list.o