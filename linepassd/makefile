CC = g++
DEBUG = -g
PROGRAM = linepassd
OS = $(shell uname -s)
ifeq ($(OS),Linux)
	MYSQL_INCLUDE = `mysql_config --cflags`
	MYSQL_LIB_PATH = `mysql_config --variable=pkglibdir`
else 
	MYSQL_INCLUDE = -I/usr/local/mysql/include
	MYSQL_LIB_PATH = /usr/local/mysql/lib/libmysqlclient.a
endif

COMMON = ../common
INC_COMMON = -I$(COMMON)
INC_CRYPTO = -I/usr/local/include/cryptopp

LIB_CRYPTO = -lcryptopp
LIB_JSON = -ljsoncpp
LIB_MYSQL = -lmysqlclient
CPP_COMMON = -L$(COMMON)

VPATH = $(CPP_COMMON)

MAKE = make

CFLAGS = -Wall -std=c++11 $(INC_CRYPTO) $(MYSQL_INCLUDE) $(INC_COMMON)
LFLAGS = -ldl -lpthread --std=c++11 -L$(MYSQL_LIB_PATH)
LIBLAGS = $(LIB_CRYPTO) $(MYSQL_LIB) $(LIB_JSON) $(LIB_MYSQL)

OBJECTS = main.o lineprogram.o mysqlc.o mysqlcpool.o granalysis.o
COMOBJ = $(COMMON)/mystring.o $(COMMON)/mainprogram.o $(COMMON)/comline.o $(COMMON)/linesecret.o $(COMMON)/threadpool.o $(COMMON)/secret.o $(COMMON)/link.o

$(PROGRAM):$(OBJECTS) $(COMOBJ)
	$(CC) $(LFLAGS) -o $(PROGRAM) $(OBJECTS) $(COMOBJ) $(LIBLAGS)
%.o:%.cpp
	$(CC) $(DEBUG) $(CFLAGS)  -c $< -o $@
$(COMMON)/%.o:
	$(MAKE) -C $(COMMON)/
clean:
	rm -rf *.o $(PROGRAM)
	$(MAKE) clean -C $(COMMON)/
