.PHONY:all
all:mysignal test

test:test.cc
	g++ -o $@ $^ -std=c++11

mysignal:mysignal.cc
	g++ -o $@  $^ -std=c++11

.PHONY:clean
clean:
	rm -f mysignal test