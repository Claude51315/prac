${CC}=gcc


all: client epoll

client:
	${CC} client.c -o client
epoll:
	${CC} epoll.c -o epoll

.phony: clean

clean:
	rm client epoll
