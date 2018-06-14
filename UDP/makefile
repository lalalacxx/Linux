.PHONY:all

all:server client

server:udp_server.c
	gcc -g $^ -o $@

client:udp_client.c
	gcc -g $^ -o $@

.PHONY:clean

clean:
	rm -rf server client
