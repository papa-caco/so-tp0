/*
 *
 *		tp0.c
 *
 *  	Created on: 1 apr. 2020
 *
 *      Author:  papa-caco
 *
 *
 */

#include "tp0.h"

int main(void)
{
	/*----------------------------------PARTE 2--------------------------------------*/
	t_log* logger 		= iniciar_logger();

	log_info(logger, "soy un log");	//Loggear "soy un log"

	t_config* config	= leer_config();

	char* ip			= config_get_string_value(config,"IP");

	char* puerto		= config_get_string_value(config,"PUERTO");

	char* mensaje 		= config_get_string_value(config,"VALOR_MSG");

	/*--------------------------PARTE 3--------------------------------------------*/
	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo
	//porque lo necesitaremos para lo que sigue.

	int conexion 		= crear_conexion(ip, puerto); 			// obtengo el socket_cliente

	enviar_mensaje(mensaje, conexion);				// enviar mensaje

	free(mensaje);
	free(puerto);
	free(ip);

	char* return_msg = recibir_mensaje(conexion);	// recibir mensaje

	log_info(logger, return_msg);					//loguear mensaje recibido

	free(return_msg);

	terminar_programa(conexion, logger, config);
}

//TODOlisto
t_log* iniciar_logger(void)
{
	return log_create("log/tp0.log", "TP0", 1, LOG_LEVEL_INFO);
}

//TODOlisto
t_config* leer_config(void)
{
	return config_create("config/tp0.config");
}

//TODOlisto
void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, para cerrar, hay que liberar lo que utilizamos:
	conexion, log y config) con las funciones de las commons y del TP
	mencionadas en el enunciado */
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
