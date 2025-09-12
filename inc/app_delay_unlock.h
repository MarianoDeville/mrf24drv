/**
 ******************************************************************************
 * @file    app_delay_unlock.h
 * @author  Lcdo. Mariano Ariel Deville
 * @brief   Implementación de delay no bloqueante.
 ******************************************************************************
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/* === Headers files inclusions =============================================== */
#include "compatibility.h"

/* === Public data type declarations ========================================== */
typedef uint32_t tick_t;

/**
 * @brief Estructura defina para el manejo del delay no bloqueante.
 *
 * @note  Definida en el header para poder utilizarla en cualquier parte del
 *        proyecto.
 */
typedef struct {

    tick_t startTime;
    tick_t duration;
    bool_t running;
} delayNoBloqueanteData_t;

/* === Public function declarations =========================================== */
/**
 * @brief  Inicializa el delay no bloqueante.
 *
 * @param  delayNoBloqueanteData_t * Puntero a la estructura con las variables.
 * @param  tick_t Duración del delay.
 * @retval None
 */
void DelayInit(delayNoBloqueanteData_t * delay, tick_t duration);

/**
 * @brief  Obtengo el estado del delay.
 *
 * @param  delayNoBloqueanteData_t * Puntero a la estructura con las variables.
 * @return bool_t Estado del delay (contando / tiempo cumplido).
 */
bool_t DelayRead(delayNoBloqueanteData_t * delay);

/**
 * @brief  Redefino el tiempo de delay.
 *
 * @param  delayNoBloqueanteData_t * Puntero a la estructura con las variables.
 * @param  tick_t Duración del delay.
 * @return None
 */
void DelayWrite(delayNoBloqueanteData_t * delay, tick_t duration);

/**
 * @brief  Reseteo la cuenta del tiempo.
 *
 * @param  delayNoBloqueanteData_t * Puntero a la estructura con las variables.
 * @return None
 */
void DelayReset(delayNoBloqueanteData_t * delay);

#endif /* API_INC_API_DELAY_H_ */
