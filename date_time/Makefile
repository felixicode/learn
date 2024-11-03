CC = gcc
CFLAGS = -Wall

all: time time_us

time: time.c
	$(CC) $(CFLAGS) -o time time.c

time_us: time_us.c
	$(CC) $(CFLAGS) -o time_us time_us.c

clean:
	rm -f time time_us
