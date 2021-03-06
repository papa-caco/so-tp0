/*
 *		utils.h
 *
 *  	Created on: 1 apr. 2020
 *
 *      Author:  papa-caco
 *
 *
 */

#ifndef UTILS_H_
#define UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>

typedef enum
{
	MENSAJE = 1,
}op_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

int 	crear_conexion		(char* ip, char* puerto);

void 	enviar_mensaje		(char* mensaje, int socket_cliente);

void* 	serializar_paquete	(t_paquete* paquete, int *bytes);

char* 	recibir_mensaje		(int socket_cliente);

void* 	recibir_buffer		(int* size, int socket_cliente);

void 	eliminar_paquete	(t_paquete* paquete);

void 	liberar_conexion	(int socket_cliente);

#endif /* UTILS_H_ */
