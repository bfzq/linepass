CC = g++

PROGRAM = linepwd

MYSQL_INCLUDE=-I/usr/local/mysql/include
MYSQL_LIB=/usr/local/mysql/lib/libmysqlclient.a
#MYSQL_INCLUDE=`mysql_config --cflags`
#MYSQL_LIB=`mysql_config --variable=pkglibdir`/libmysqlclient.a

INC_CRYPTO = -I/usr/local/include/cryptopp
LIB_CRYPTO = /usr/local/lib/libcryptopp.a

MAKE = make

CFLAGS += -Wall -g -std=c++11 $(INC_CRYPTO) $(MYSQL_INCLUDE)
LFLAGS += -ldl -lpthread -g --std=c++11 
LIBLAGS += $(LIB_CRYPTO) $(MYSQL_LIB)

OBJECTS = main.o mainprogram.o comline.o lineprogram.o linesecret.o mysqlc.o link.o threadpool.o mysqlcpool.o


$(PROGRAM):$(OBJECTS)
	$(CC) $(LFLAGS) -o $(PROGRAM) $(OBJECTS) $(LIBLAGS)
%.o:%.cpp
	$(CC) $(DEBUG) $(CFLAGS)  -c $< -o $@
clean:
	rm -rf *.o $(PROGRAM)
