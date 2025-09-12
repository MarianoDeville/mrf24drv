/*
 * compatibility.h
 *
 *  Created on: Apr 4, 2025
 *      Author: Mariano Deville
 */

#ifndef INC_COMPATIBILITY_H_
#define INC_COMPATIBILITY_H_

#include <stdbool.h>
#include <stdint-gcc.h>
#include <unistd.h>

/**
 * Macros
 */
#define VACIO      (0X00)
#define delay_t(x) sleep(x)
#define bool_t     bool

/**
 * Respuestas de las funciones de envío de datos.
 */
typedef enum {

    OK,
    BUFFER_VACIO,
    SIN_DATOS,
    ERROR_SIZE,
    ERROR_TRANSMISION,
} estado_TX_RX_t;

#endif /* INC_COMPATIBILITY_H_ */
