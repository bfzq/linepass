DEBUG = -g
CC = g++

PROGRAM = linepass

COMMON = ../common
INC_COMMON = -I$(COMMON)
MAKE = make

INC_DIR = -I$(COMMON) -I/usr/local/include/cryptopp
LIB_DIR = /usr/local/lib/libcryptopp.a


CFLAGS = -Wall -std=c++11 $(INC_DIR) $(INC_COMMON)
LFLAGS += -ldl -lpthread --std=c++11


OBJ = main.o command.o mainprogram.o comline.o link.o threadpool.o logs.o linesecret.o secret.o comprogram.o

$(PROGRAM):$(OBJ)
	$(CC) $(DEBUG) $(LFLAGS) -o $(PROGRAM) $(OBJ) $(LIB_DIR)
%.o:$(COMMON)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS)  -c $< -o $@
%.o:%.cpp
	$(CC) $(DEBUG) $(CFLAGS)  -c $< -o $@
clean:
	rm -rf *.o $(PROGRAM)
