.PHONY:all
all:client server

client:client.cc
	g++ -o $@ $^ -std=c++11 -g
server:server.cc 
	g++ -o $@ $^ -std=c++11 -g

.PHONY:clean
clean:
	rm -f server client