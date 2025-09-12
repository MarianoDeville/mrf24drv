/**
 *********************************************************************************
 * @file    drv_MRF24J40_port.h
 * @author  Lcdo. Mariano Ariel Deville
 * @brief	Archivo cabecera para el archivo drv_MRF24J40_port.c
 *********************************************************************************
 * @attention Este archivo asegura la portabilidad del driver (drv_MRF24J40.c)
 *
 *********************************************************************************
 */
#ifndef INC_DRV_MRF24J40_PORT_H_
#define INC_DRV_MRF24J40_PORT_H_

/* === Archivos cabecera ====================================================== */
#include "compatibility.h"

/* === Definición de macros públicas ========================================== */
#define _1_BYTE      (0x01)
#define _2_BYTES     (0x02)
#define SHIFT_BYTE   (0X08)
#define TIME_OUT_SPI 100

/* === Declaración de tipo de datos públicos ================================== */
/**
 * @brief Respuesta de las funciones
 */
typedef enum {

    SPI_COMM_OK,
    SPI_COMM_ERROR,
} spi_state_t;

/* === Declaración de funciones públicas ====================================== */
/**
 * @brief  Inicialización del hardware relacionado con el módulo.
 *
 * @param  None.
 * @return None.
 */
void InicializoPines(void);

/**
 * @brief  Escribo en el pin destinado a CS.
 *
 * @param  bool_t Estado de salida.
 * @return None.
 */
void SetCSPin(bool_t estado);

/**
 * @brief  Escribo en el pin destinado a Wake.
 *
 * @param  bool_t Estado de salida.
 * @return None.
 */
void SetWakePin(bool_t estado);

/**
 * @brief  Escribo en el pin destinado a Reset.
 *
 * @param  bool_t Estado de salida.
 * @return None.
 */
void SetResetPin(bool_t estado);

/**
 * @brief  Devuelvo el estado del pin interrup del módulo.
 *
 * @param  None.
 * @return bool_t Estado del pin.
 */
bool_t IsMRF24Interrup(void);

/**
 * @brief  Escribo en el puerto SPI 1 byte.
 *
 * @param  uint8_t * Puntero al dato a enviar por el puerto.
 * @return spi_state_t Estado del envío.
 */
spi_state_t WriteByteSPIPort(uint8_t * dato);

/**
 * @brief  Escribo en el puerto SPI 2 bytes.
 *
 * @param  uint16_t * Puntero al dato a enviar por el puerto.
 * @return spi_state_t Estado del envío.
 */
spi_state_t Write2ByteSPIPort(uint16_t * dato);

/**
 * @brief  Leo en el puerto SPI.
 *
 * @param  uint8_t Puntero a la variable que almacena la respuesta.
 * @return spi_state_t Estado del envío.
 */
spi_state_t ReadByteSPIPort(uint8_t * respuesta);

#endif /* INC_DRV_MRF24J40_PORT_H_ */
