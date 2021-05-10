

CC = gcc

CFLAGS = -Wall

TARGET = lifegame

SRCS = lifegame.c

OBJS = $(SRCS:.c=.o)


%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


all: clean build

build: $(TARGET)

clean:
	$(RM) $(OBJS) $(TARGET)


.PHONY: all build clean

