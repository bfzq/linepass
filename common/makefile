DEBUG = -g
CC = g++
MAKE = make

INC_DIR := -I/usr/local/include/cryptopp


CFLAGS := -Wall -std=c++11 $(INC_DIR)

OBJ=mystring.o mainprogram.o comline.o link.o threadpool.o logs.o linesecret.o secret.o
all:$(OBJ)
%.o:%.cpp
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@
clean:
	rm -rf *.o
