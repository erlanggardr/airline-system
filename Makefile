CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/main.c src/flight.c src/database.c src/reservation.c
OBJS = $(SRCS:.c=.o)
TARGET = airline_system

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
