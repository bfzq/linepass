build:client server
client:
	make -C linepass
server:
	make -C linepassd
clean:
	make clean -C linepass
	make clean -C linepassd
install:
