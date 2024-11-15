CC=gcc
EXEC=program.out
EXEC2=program2.out
GRUPO=G1
NTAR=2

SRC_DIR=src
SRC2_DIR=src2
OBJ_DIR=obj
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
SRC2_FILES=$(wildcard $(SRC2_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ2_FILES=$(patsubst $(SRC2_DIR)/%.c,$(OBJ_DIR)/%_src2.o,$(SRC2_FILES))
INCLUDE=-I./incs/
LIBS=

CFLAGS=-Wall -Wextra -Wpedantic -O3
LDFLAGS=-Wall -lm

all: $(OBJ2_FILES) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o build/$(EXEC) $(OBJ_FILES) $(INCLUDE) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDE)

$(OBJ_DIR)/%_src2.o: $(SRC2_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDE)

build/$(EXEC2): $(OBJ2_FILES)
	$(CC) $(CFLAGS) -o build/$(EXEC2) $(OBJ2_FILES) $(INCLUDE) $(LIBS)

.PHONY: clean folders send
clean:
	rm -f $(OBJ_FILES) $(OBJ2_FILES)
	rm -f build/$(EXEC) build/$(EXEC2)
	rm -f doc*.txt

folders:
	mkdir -p src src2 obj incs build docs

send:
	tar czf $(GRUPO)-$(NTAR).tgz --transform 's,^,$(GRUPO)-$(NTAR)/,' Makefile src src2 incs docs

run: build/$(EXEC)
	./build/$(EXEC) -s f

run2: build/$(EXEC2)
	./build/$(EXEC2) -d 3

#doxygen:
#	doxygen config
#	./docs/latex/Make
