DEBUG = -g
CC = g++

PROGRAM = linepass

COMMON = ../common
INC_COMMON = -I$(COMMON)
MAKE = make

INC_DIR = -I$(COMMON) -I/usr/local/include/cryptopp
LIB_DIR = -lcryptopp -ljsoncpp


CFLAGS = -Wall -std=c++11 $(INC_DIR) $(INC_COMMON)
LFLAGS += -ldl -lpthread --std=c++11


OBJ = main.o command.o comprogram.o
COMOBJ = $(COMMON)/mainprogram.o $(COMMON)/comline.o $(COMMON)/link.o $(COMMON)/threadpool.o $(COMMON)/logs.o $(COMMON)/linesecret.o $(COMMON)/secret.o

$(PROGRAM):$(OBJ) $(COMOBJ)
	$(CC) $(DEBUG) $(LFLAGS) -o $(PROGRAM) $(OBJ) $(COMOBJ) $(LIB_DIR)
$(COMMON)/%.o:
	$(MAKE) -C $(COMMON)/
%.o:%.cpp
	$(CC) $(DEBUG) $(CFLAGS)  -c $< -o $@
clean:
	rm -rf *.o $(PROGRAM)
	$(MAKE) clean -C $(COMMON)/
