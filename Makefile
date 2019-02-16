CC  := mips-linux-gnu-gcc
SRC := src
OBJ := obj

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: bin/main
	ssh root@192.168.1.1 "[ -L /lib/ld.so.1 ] || ln -s /lib/libc.so /lib/ld.so.1"
	ssh root@192.168.1.1 "rm -f /tmp/main"
	scp bin/main root@192.168.1.1:/tmp/main
	ssh root@192.168.1.1 "/tmp/main"

bin/main: $(OBJECTS)
	mkdir -p bin
	$(CC) $(OBJECTS) -o bin/main

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p obj
	$(CC) -c $< -o $@

helper:
	scp -r utils/ root@192.168.1.1:

clean:
	rm -f bin/* obj/* **/*~
