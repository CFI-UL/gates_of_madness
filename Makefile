CC := mips-linux-gnu-gcc
CFLAGS := -march=34kc -L./lib:./usr/lib

SRC := src
OBJ := obj

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: paths ld.so.1 $(OBJECTS)
	ssh root@192.168.1.1 "rm -f /tmp/test"
	scp bin/test root@192.168.1.1:/tmp/test
	ssh root@192.168.1.1 "/tmp/test"

paths:
	mkdir -p bin obj

$(OBJ)/%.o: $(SRC)/%.c
	LD_LIBRARY_PATH=./lib:./usr/lib $(CC) -I$(SRC) $(CLFAGS) -c $< -o $@
	$(CC) -I$(SRC) -c $< -o $@

ld.so.1:
	ssh root@192.168.1.1 "[ -L /lib/ld.so.1 ] || ln -s /lib/libc.so /lib/ld.so.1"

helper:
	scp -r utils/ root@192.168.1.1:

clean:
	rm -f bin/* obj/* **/*~
