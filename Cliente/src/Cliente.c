/*
 * Modelo ejemplo de un Cliente que envia mensajes a un Server.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define IP "127.0.0.1"
#define PUERTO "6667"
#define PACKAGESIZE 1024	// Define cual va a ser el size maximo del paquete a enviar

int main(){

	/*
	 *  Obtiene los datos de red
	 *
	 */
	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		// No importa si uso IPv4 o IPv6
	hints.ai_socktype = SOCK_STREAM;	// Indica que usaremos el protocolo TCP

	getaddrinfo(IP, PUERTO, &hints, &serverInfo); // Notar que le pasamos NULL como IP, ya que le indicamos que use localhost en AI_PASSIVE


	/*
	 * Obtiene un socket (un file descriptor), utilizando la estructura serverInfo que generamos antes
	 *
	 */
	/* Necesitamos un socket que escuche las conecciones entrantes */
	int serverSocket;
	serverSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

	/*
	 * 	Le indicamos al socket que se conecte.
	 *
	 */
	connect(serverSocket, serverInfo->ai_addr, serverInfo->ai_addrlen);
	freeaddrinfo(serverInfo);	// No lo necesitamos mas

	/*
	 * 	Enviamos los paquetes.
	 */
	int enviar = 1;
	char message[PACKAGESIZE];

	while(enviar){
		gets(message);
		if (!strcmp(message,"exit")) enviar = 0;			// Chequeo que el usuario no quiera salir
		if (enviar) send(serverSocket, message, strlen(message) + 1, 0);
	}


	/*
	 * Cerramos las conexiones.
	 */

	close(serverSocket);
	return 0;
}
