/*
 *
 *		tp0.h
 *
 *  	Created on: 1 apr. 2020
 *
 *      Author:  papa-caco
 *
 *
 */

#ifndef TP0_H_
#define TP0_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"

t_log* 		iniciar_logger		(void);

t_config*	leer_config			(void);

void 		terminar_programa	(int socket_cliente, t_log* logger, t_config* config);

#endif /* TP0_H_ */
