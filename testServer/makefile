all: clean testServer

testServer:
	gcc -Wall -Wextra -g -fPIC src/utils.c -c -o	debug/utils.o -lcommons -lpthread
	gcc -Wall -Wextra -g -fPIC src/servidor.c -c -o debug/servidor.o -lcommons -lpthread
	gcc -Wall -Wextra -g debug/utils.o debug/servidor.o -o bin/testServer -lcommons -lpthread

clean:
	rm -f ./debug/*.o ./bin/testServer