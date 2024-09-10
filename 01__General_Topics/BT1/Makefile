.PHONY: all clean 


LIB_NAME 	:= teststatic

CUR_DIR 	:= .
BIN_DIR 	:= $(CUR_DIR)/bin
INC_DIR 	:= $(CUR_DIR)/inc

LIB_DIR 	:= $(CUR_DIR)/libs
LIB_SHARED 	:= $(LIB_DIR)/shared
LIB_STATIC 	:= $(LIB_DIR)/static

OBJ_DIR 	:= $(CUR_DIR)/obj
SRC_DIR 	:= $(CUR_DIR)/src

# Tells the compiler to add 'INC_DIR' to the list of directories to search for header files
INC_FLAGS 	:= -I $(INC_DIR)

CC 			:= gcc


mk_objs:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS)

# Create the object files for the static library (without -fPIC)
	$(CC) -c $(SRC_DIR)/my_SumOperation.c -o $(OBJ_DIR)/my_SumOperation.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/my_Hi.c -o $(OBJ_DIR)/my_Hi.o $(INC_FLAGS)

mk_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_NAME).a $(OBJ_DIR)/my_SumOperation.o $(OBJ_DIR)/my_Hi.o

all: mk_objs mk_static
	$(CC)   $(OBJ_DIR)/main.o -L$(LIB_STATIC) -l$(LIB_NAME) -o $(BIN_DIR)/statically-linked

clean:
	rm -rf $(OBJ_DIR)/* 
	rm -rf $(LIB_STATIC)/*
	rm -rf $(BIN_DIR)/*



# #Static lib
# mk_objs_static:
# 	$(CC) -c -o $(OBJ_DIR)/main.o main.c $(INC_FLAGS)
# 	$(CC) -c -o $(OBJ_DIR)/mymath.o $(SRC_DIR)/mymath.c $(INC_FLAGS)
# 	$(CC) -c -o $(OBJ_DIR)/hivion.o $(SRC_DIR)/hivion.c $(INC_FLAGS)
# 	$(CC) -c -o $(OBJ_DIR)/hello.o $(SRC_DIR)/hello.c $(INC_FLAGS)

# mk_lib_static:
# 	ar rcs $(LIB_STATIC)/lib$(LIB_NAME).a $(OBJ_DIR)/*.o

# link_static: mk_objs_static mk_lib_static
# 	$(CC) $(OBJ_DIR)/main.o -L$(LIB_STATIC) -l$(LIB_NAME) -o $(BIN_DIR)/use_static_lib


# clean:
# 	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/* $(LIB_SHARED)/* $(LIB_STATIC)/*

