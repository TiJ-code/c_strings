CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = main

SRC = $(wildcard *.c)

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
