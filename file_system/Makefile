CC = gcc
CFLAGS = -Wall

all: read write ls

read: read.o
	$(CC) $(CFLAGS) -o read read.o

read.o: read.c
	$(CC) $(CFLAGS) -c read.c

write: write.o
	$(CC) $(CFLAGS) -o write write.o

write.o: write.c
	$(CC) $(CFLAGS) -c write.c

ls: ls.o
	$(CC) $(CFLAGS) -o ls ls.o

ls.o: ls.c
	$(CC) $(CFLAGS) -c ls.c

clean:
	rm -f read write ls *.o
