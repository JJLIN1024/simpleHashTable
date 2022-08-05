CC=gcc
CFLAGS=-Wall -lm -std=c99
SRC=hashtable.c prime.c main.c
OBJS=hashtable.o prime.o main.o
HEADERS=hashtable.h prime.h
TARGET=hash

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@

debug: $(SRC)
	$(CC) $^ $(CFLAGS) -g -o $@

main.o: hashtable.h 

hashtable.o: hashtable.h prime.h

prime.o: prime.h

check: $(SRC) $(HEADERS)
	cppcheck --std=c99 $^

valgrind: $(TARGET)
	valgrind ./$(TARGET)

clean:
	rm -f *.o $(TARGET) debug