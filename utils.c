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
	t_buffer* 	_buffer = malloc(sizeof(t_buffer));
	void* 		_stream;
	t_paquete* 	paquete;
	void* 		a_enviar;
	int 		bytes;

	_buffer -> size = sizeof(int) + strlen(mensaje);
	_stream = malloc(_buffer -> size);
	memcpy(_stream, &mensaje,sizeof(strlen (mensaje)));		//por ahora no sumamos caracter centinela
	_buffer -> stream = _stream;

	paquete =  malloc(sizeof(paquete));
	paquete -> codigo_operacion = MENSAJE;
	paquete -> buffer = _buffer;

	bytes = _buffer -> size + sizeof(int) * 2;

	// tamaño del mensaje en bytes (= _buffer -> size) + el tamaño de 2 int: code_op + buffer->size

	a_enviar = serializar_paquete(paquete, &bytes);

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
	int a_enviar_size;
	memcpy(&(a_enviar_size), bytes, sizeof(int));

	void * a_enviar = malloc(a_enviar_size);
 	int offset = 0;

	memcpy(a_enviar + offset , &(paquete->codigo_operacion), sizeof(int));
	offset+= sizeof(int);
	memcpy(a_enviar + offset, &(paquete->buffer->size), sizeof(int));
	offset+= sizeof(int);
	memcpy(a_enviar + offset, paquete->buffer->stream, paquete->buffer->size);

	return a_enviar;
}

// tODOlisto
char* recibir_mensaje(int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(paquete));

	recv(socket_cliente, &(paquete -> codigo_operacion), sizeof(int), MSG_WAITALL);
	recv(socket_cliente, &(paquete -> buffer -> size), sizeof(int), MSG_WAITALL);
	recv(socket_cliente, &(paquete -> buffer -> stream), paquete -> buffer -> size, MSG_WAITALL);
	char* mensaje = malloc(sizeof(paquete -> buffer -> stream));

	if (paquete -> codigo_operacion == MENSAJE) {
		memcpy(&(mensaje),paquete -> buffer -> stream, paquete -> buffer -> size);
	} else {
		mensaje = "Operacion desconocida.";
	}
	return mensaje;
}

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
