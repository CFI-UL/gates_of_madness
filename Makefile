CC=mips-linux-gnu-gcc
CFLAGS=-march=34kc -L./lib:./usr/lib

all: build ld.so.1
	ssh root@192.168.1.1 "rm /tmp/test"
	scp bin/test root@192.168.1.1:/tmp/test
	ssh root@192.168.1.1 "/tmp/test"

build:
	[ -d bin ] || mkdir bin
	LD_LIBRARY_PATH=./lib:./usr/lib  $(CC) src/test.c $(CLFAGS) -o bin/test

ld.so.1:
	ssh root@192.168.1.1 "[ -L /lib/ld.so.1 ] || ln -s /lib/libc.so /lib/ld.so.1"

clean:
	rm bin/*
