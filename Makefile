CC=g++
CFLAGS=-pthread -fpermissive

all:
	$(CC) $(CFLAGS) hello_world.cpp -o hello_world