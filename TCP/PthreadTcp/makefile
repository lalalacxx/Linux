.PHONY:all

all:server client

server:tcp_server.c
	gcc -g $^ -o $@ -lpthread

client:tcp_client.c
	gcc -g $^ -o $@

.PHONY:clean

clean:
	rm -rf server client
