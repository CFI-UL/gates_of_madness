CC=mips-linux-gnu-gcc
CFLAGS=-march=34kc -L./lib:./usr/lib

all: build
	scp bin/test root@192.168.1.1:/tmp/test
	ssh root@192.168.1.1 "/tmp/test"

build:
	LD_LIBRARY_PATH=./lib:./usr/lib  $(CC) src/test.c $(CLFAGS) -o bin/test

clean:
	rm bin/*
