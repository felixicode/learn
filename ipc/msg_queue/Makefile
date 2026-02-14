CC = gcc
CFLAGS = -Wall

all: sever client

sever: sever.o
	$(CC) $(CFLAGS) -o sever sever.o

sever.o: sever.c
	$(CC) $(CFLAGS) -c sever.c

client: client.o
	$(CC) $(CFLAGS) -o client client.o

client.o: client.c
	$(CC) $(CFLAGS) -c client.c

clean:
	rm -f sever client *.o
