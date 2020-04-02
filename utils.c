/*
 *		utils.c
 *
 *  	Created on: 1 apr. 2020
 *
 *      Author:  papa-caco
 *
 *
 */

#include "utils.h"

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error");

	freeaddrinfo(server_info);

	return socket_cliente;
}

//TODOlisto
void enviar_mensaje(char* mensaje, int socket_cliente)
{
	t_paquete* 	paquete = malloc(sizeof(t_paquete));

	paquete -> codigo_operacion = MENSAJE;

	paquete -> buffer = malloc(sizeof(t_buffer));
	paquete -> buffer -> size = strlen(mensaje) + 1;

	// el valor de size es  la cantidad de bytes del mensaje sin el char centinela

	paquete -> buffer -> stream = malloc(paquete -> buffer -> size);

	memcpy(paquete -> buffer -> stream , mensaje, paquete -> buffer -> size);

	int bytes = paquete -> buffer -> size + 2 * sizeof(int) ;

	// el valor de bytes es tamaño del mensaje en bytes (= _buffer -> size)
	// + el tamaño de 2 int: code_op + buffer->size

	void* a_enviar = serializar_paquete(paquete, &bytes);

	send(socket_cliente, a_enviar, bytes, 0 );

	free(a_enviar);
	eliminar_paquete(paquete);
}

//TODOlisto
/*
 * Recibe un paquete a serializar, y un puntero a un int en el que dejar
 * el tamaño del stream de bytes serializados que devuelve
 */
void* serializar_paquete(t_paquete* paquete, int *bytes)
{

	void * a_enviar = malloc(*bytes);
 	int offset = 0;

	memcpy(a_enviar + offset , &(paquete->codigo_operacion), sizeof(int));
	offset+= sizeof(int);
	memcpy(a_enviar + offset, &(paquete->buffer->size), sizeof(int));
	offset+= sizeof(int);
	memcpy(a_enviar + offset, paquete->buffer->stream, paquete->buffer->size);
	offset += paquete->buffer->size;

	return a_enviar;
}

// tODOlisto
char* recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
		return buffer;
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

/*
char* recibir_mensaje(int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(paquete));

	recv(socket_cliente, &(paquete -> codigo_operacion), sizeof(int), MSG_WAITALL);
	recv(socket_cliente, &(paquete -> buffer -> size), sizeof(int), MSG_WAITALL);
	recv(socket_cliente, paquete -> buffer -> stream, paquete -> buffer -> size, MSG_WAITALL);
	char* mensaje = malloc(paquete -> buffer -> size);

	if (paquete -> codigo_operacion == MENSAJE) {
		memcpy(&(mensaje),paquete -> buffer -> stream, paquete -> buffer -> size);
	} else {
		mensaje = "Operacion desconocida.";
	}
	return mensaje;
}
*/



void eliminar_paquete(t_paquete* paquete)
{
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}
