DEBUG = -g
CC = g++

PROGRAM = linepass

COMMON = ../common/

MAKE = make

INC_DIR = -I$(COMMON) -I/usr/local/include/cryptopp
LIB_DIR = /usr/local/lib/libcryptopp.a


CFLAGS = -Wall -std=c++11 $(INC_DIR)
LFLAGS += -ldl -lpthread --std=c++11


OBJ = main.o command.o comprogram.o mainprogram.o comline.o link.o threadpool.o logs.o linesecret.o

$(PROGRAM):$(OBJ)
	$(CC) $(DEBUG) $(LFLAGS) -o $(PROGRAM) $(OBJ) $(LIB_DIR)
%.o:$(COMMON)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS)  -c $< -o $@
%.o:%.cpp
	$(CC) $(DEBUG) $(CFLAGS)  -c $< -o $@
clean:
	rm -rf *.o $(PROGRAM)
