CC  := mips-linux-gnu-gcc
SRC := src
OBJ := obj

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: build
	ssh root@192.168.1.1 "[ -L /lib/ld.so.1 ] || ln -s /lib/libc.so /lib/ld.so.1"
	ssh root@192.168.1.1 "rm -f /tmp/sesame"
	scp bin/sesame root@192.168.1.1:/tmp/sesame
	ssh root@192.168.1.1 "/tmp/sesame"

build: bin/sesame

bin/sesame: $(OBJECTS)
	mkdir -p bin
	$(CC) $(OBJECTS) -o bin/sesame

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p obj
	$(CC) -c $< -o $@

install: build
	scp -r etc/ usr/ root@192.168.1.1:/
	scp bin/sesame root@192.168.1.1:/usr/sbin/sesame
	ssh root@192.168.1.1 "/etc/init.d/sesamed enabled || /etc/init.d/sesamed enable"

helper:
	scp -r utils/ root@192.168.1.1:

clean:
	rm -f bin/* obj/* **/*~
