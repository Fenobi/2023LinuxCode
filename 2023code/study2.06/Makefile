.PYTHON:all
all:mybin myexec

mybin:mybin.c
	gcc -o $@ $^ -std=c99

myexec:myexec.c
	gcc -o $@ $^ -std=c99 

.PYTHON:clean
clean:
	rm -f myexec mybin 