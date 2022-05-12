all: exec

c-files: task23.c
	gcc -g -c -o task23.o task23.c

exec: c-files task23.o
	gcc -g task23.o -o task23

.PHONY: clean
clean:
	rm -rf ./*.o main
