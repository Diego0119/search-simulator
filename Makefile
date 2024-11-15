CC=gcc
EXEC=program.out
GRUPO=G1
NTAR=2

SRC_DIR=src
OBJ_DIR=obj
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCLUDE=-I./incs/
LIBS=

CFLAGS=-Wall -Wextra -Wpedantic -O3
LDFLAGS= -Wall -lm 

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o build/$(EXEC) $(OBJ_FILES) $(INCLUDE) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDE)

.PHONY: clean folders send
clean:
	rm -f $(OBJ_FILES)
	rm -f build/$(EXEC)
	rm -f doc*.txt

folders:
	mkdir -p src obj incs build docs

send:
	tar czf $(GRUPO)-$(NTAR).tgz --transform 's,^,$(GRUPO)-$(NTAR)/,' Makefile src incs docs

run: build/$(EXEC)
	./build/$(EXEC) -d 10

#doxygen:
#	doxygen config
#	./docs/latex/Make