.PHONY: install all clean 


LIB_NAME	:= testshared

CUR_DIR		:= .
BIN_DIR		:= $(CUR_DIR)/bin
$(shell mkdir -p $(BIN_DIR))
INC_DIR		:= $(CUR_DIR)/inc

LIB_DIR		:= $(CUR_DIR)/libs
LIB_SHARED	:= $(LIB_DIR)/shared
$(shell mkdir -p $(LIB_SHARED))
LIB_STATIC	:= $(LIB_DIR)/static
# $(shell mkdir -p $(LIB_STATIC))

OBJ_DIR		:= $(CUR_DIR)/obj
$(shell mkdir -p $(OBJ_DIR))

SRC_DIR		:= $(CUR_DIR)/src

# Tells the compiler to add 'INC_DIR' to the list of directories to search for header files
INC_FLAGS	:= -I $(INC_DIR)

CC		:= gcc


all: mk_objs mk_shared install
	$(CC)  $(OBJ_DIR)/main.o -L$(LIB_SHARED) -l$(LIB_NAME) -o $(BIN_DIR)/use-shared-library

mk_objs:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS)

# Compile with -fPIC to generate position-independent code (PIC),
# allowing the object files to be loaded at any address in memory.
	$(CC) -c -fPIC $(SRC_DIR)/my_SumOperation.c -o $(OBJ_DIR)/my_SumOperation.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/my_Hi.c -o $(OBJ_DIR)/my_Hi.o $(INC_FLAGS)

mk_shared:
# Lib's name must be: lib + name_of_lib, e.g. libtestshared
	$(CC) -shared $(OBJ_DIR)/my_SumOperation.o $(OBJ_DIR)/my_Hi.o -o $(LIB_SHARED)/lib$(LIB_NAME).so

install:
# need permission
	sudo cp -f $(LIB_SHARED)/lib$(LIB_NAME).so /usr/lib

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(LIB_DIR)
	rm -rf $(BIN_DIR)

