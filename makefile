clean:
	-rm -f debug/*
	-rm -f bin/*

default:
	-gcc  -g -Wall  -c src/tp0.c -o debug/tp0.o
	-gcc  -g -Wall  -c src/utils.c -o debug/utils.o
	-gcc   debug/tp0.o  debug/utils.o -g -Wall  -lreadline -lcommons  -o bin/tp0

all: clean default
