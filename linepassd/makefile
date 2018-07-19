CC = g++
DEBUG = -g
PROGRAM = linepassd
OS = $(shell uname -s)
ifeq ($(OS),Linux)
	MYSQL_INCLUDE = `mysql_config --cflags`
	MYSQL_LIB = `mysql_config --variable=pkglibdir`/libmysqlclient.a
else 
	MYSQL_INCLUDE = -I/usr/local/mysql/include
	MYSQL_LIB = /usr/local/mysql/lib/libmysqlclient.a
endif

COMMON = ../common
INC_COMMON = -I$(COMMON)
INC_CRYPTO = -I/usr/local/include/cryptopp
LIB_CRYPTO = /usr/local/lib/libcryptopp.a
CPP_COMMON = -L$(COMMON)

VPATH = $(CPP_COMMON)

MAKE = make

CFLAGS = -Wall -std=c++11 $(INC_CRYPTO) $(MYSQL_INCLUDE) $(INC_COMMON)
LFLAGS = -ldl -lpthread --std=c++11 
LIBLAGS = $(LIB_CRYPTO) $(MYSQL_LIB)

OBJECTS = main.o mainprogram.o comline.o lineprogram.o linesecret.o \
	mysqlc.o link.o threadpool.o mysqlcpool.o secret.o


$(PROGRAM):$(OBJECTS)
	$(CC) $(LFLAGS) -o $(PROGRAM) $(OBJECTS) $(LIBLAGS)
%.o:%.cpp
	$(CC) $(DEBUG) $(CFLAGS)  -c $< -o $@
%.o:$(COMMON)/%.cpp
	$(CC) $(DEBUG) $(CFLAGS)  -c $< -o $@
clean:
	rm -rf *.o $(PROGRAM)
