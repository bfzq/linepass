build:client server
client:
	make -C linepass
server:
	make -C linepassd
clean:
	make clean -C linepass
	make clean -C linepassd
install:
	cp linepassd/linepassd /usr/local/bin/
	cp linepass/linepass /usr/local/bin/
uninstall:
	rm -rf /usr/local/bin/linepass*
