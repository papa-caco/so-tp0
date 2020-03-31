/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	log_info(logger, "soy un log");	//Loggear "soy un log"

	config = leer_config();
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo
	//porque lo necesitaremos para lo que sigue.

	//crear conexion

	//enviar mensaje

	//recibir mensaje

	//loguear mensaje recibido

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
	close(conexion);
}
