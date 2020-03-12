all: cms
 
CC = gcc
CFLAGS = -Wall -Os -I.
LDFLAGS = 
 
DEPS = $(wildcard src/*.h)
 
SRC = $(wildcard src/*.c) crypto/md5.c
 
OBJ = $(patsubst %.c, %.o, $(SRC))
 
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
 
cms: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
 
.PHONY: clean
 
clean:
	rm -f cms */*.o
