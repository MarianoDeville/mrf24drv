/**
 *******************************************************************************
 * @file    drv_MRF24J40.h
 * @author  Lcdo. Mariano Ariel Deville
 * @brief	Archivo cabecera para el archivo drv_MRF24J40.c
 * @version 0.1
 * @date 2025/02/01
 *******************************************************************************
 */
#ifndef INC_DRV_MRF24J40_H_
#define INC_DRV_MRF24J40_H_

/* === Archivos cabecera ====================================================== */
#include "compatibility.h"

/* === Definición de macros públicas ========================================== */
#define BROADCAST      (0xFFFF)
#define LARGE_MAC_SIZE 8
#define SEC_KEY_SIZE   16
#define BUFFER_SIZE    128

/* === Declaración de tipo de datos públicos ================================== */
/**
 * @brief Canales disponibles para el IEEE 802.15.4.
 */
typedef enum {

    CH_11 = 0x03,
    CH_12 = 0x13,
    CH_13 = 0x23,
    CH_14 = 0x33,
    CH_15 = 0x43,
    CH_16 = 0x53,
    CH_17 = 0x63,
    CH_18 = 0x73,
    CH_19 = 0x83,
    CH_20 = 0x93,
    CH_21 = 0xA3,
    CH_22 = 0xB3,
    CH_23 = 0xC3,
    CH_24 = 0xD3,
    CH_25 = 0xE3,
    CH_26 = 0xF3
} channel_list_t;

/**
 * @brief Respuesta de las funciones.
 */
typedef enum {

    INIT_FAIL,
    INIT_OK,
    TRANS_COMPLETED,
    DIRECTION_EMPTY,
    MSG_PRESENT,
    MSG_READ,
    TO_LONG_MSG,
    BUFFER_EMPTY,
    TIME_OUT_OCURRED,
    OPERATION_FAIL,
    OPERATION_OK,
    UNEXPECTED_ERROR,
    INVALID_VALUE,
} mrf24_state_t;

/**
 * @brief Estructura con la información de configuración del dispositivo.
 */
typedef struct {

    channel_list_t channel;
    uint8_t sequence_number;
    uint16_t panid;
    uint16_t address;
    uint16_t intervalo;
    uint8_t mac[8];
    uint8_t security_key[16];
} mrf24_data_config_t;

/**
 * @brief Estructura con la información de transmisión.
 */
typedef struct {

    uint16_t dest_panid;
    uint16_t dest_address;
    uint16_t origin_address;
    char buffer[BUFFER_SIZE];
    uint8_t buffer_size;
} mrf24_data_out_t;

/**
 * @brief Estructura con la información de recepción.
 */
typedef struct {

    uint16_t panid;
    uint16_t address;
    uint8_t rssi;
    uint8_t buffer[BUFFER_SIZE];
    uint8_t buffer_size;
} mrf24_data_in_t;

/**
 * @brief Estructura con la lista de dispositivos cercanos.
 */
typedef struct {

    uint8_t channel;
    uint16_t panid;
    uint8_t long_address[8];
    uint16_t short_address;
    uint8_t rssi;
} MRF24_discover_nearby_t;

/* === Declaración de funciones públicas ====================================== */
/**
 * @brief  Inicialización del módulo MRF24J40MA.
 *
 * @param  None.
 * @return mrf24_state_t Estado de la operación (TIME_OUT_OCURRIDO,
 *                       INICIALIZACION_OK).
 */
mrf24_state_t MRF24J40Init(void);

/**
 * @brief  Actualizo el canal de trabajo.
 *
 * @param  channel_list_t Nuevo canal.
 * @return mrf24_state_t Estado de la operación (INVALID_VALUE, OPERATION_OK).
 *
 * @note   Se comprueba la integridad del dato.
 */
mrf24_state_t MRF24SetChannel(channel_list_t ch);

/**
 * @brief  Actualizo el PANID de trabajo.
 *
 * @param  uint16_t Nuevo PANID (uint16_t).
 * @return mrf24_state_t Estado de la operación (INVALID_VALUE, OPERATION_OK).
 *
 * @note   Se comprueba la integridad del dato.
 */
mrf24_state_t MRF24SetPanId(uint16_t pan_id);

/**
 * @brief  Actualizo la dirección corta del dispositivo.
 *
 * @param  uint16_t Nueva dirección (uint16_t).
 * @return mrf24_state_t Estado de la operación (INVALID_VALUE, OPERATION_OK).
 *
 * @note   Se comprueba la integridad del dato.
 */
mrf24_state_t MRF24SetAdd(uint16_t add);

/**
 * @brief  Actualizo el número de secuancia de las comunicaciones salientes.
 *
 * @param  Nuevo número de secuencia (uint16_t).
 * @return mrf24_state_t Estado de la operación (OPERATION_OK).
 */
mrf24_state_t MRF24SetSec(uint16_t sec);

/**
 * @brief  Actualizo la dirección larga del dispositivo.
 *
 * @param  uint8_t Nueva dirección (8 bytes).
 * @return mrf24_state_t Estado de la operación (INVALID_VALUE, OPERATION_OK).
 *
 * @note   Se comprueba la integridad del dato.
 */
mrf24_state_t MRF24SetMAC(uint8_t mac[8]);

/**
 * @brief  Actualizo la llave de seguridad para la encriptación.
 *
 * @param  uint8_t Nueva llave (16 bytes).
 * @return mrf24_state_t Estado de la operación (INVALID_VALUE, OPERATION_OK).
 *
 * @note   Se comprueba la integridad del dato.
 */
mrf24_state_t MRF24SetSecurityKey(uint8_t security_key[16]);

/**
 * @brief  Envío la información almacenada en la estructura de salida.
 *
 * @param  mrf24_data_out_t * Puntero a la estructura que contiene la información
 *                            de envío.
 * @return mrf24_state_t Estado de la operación (OPERACION_NO_REALIZADA,
 *         TRANSMISION_REALIZADA, NO_DIRECCION, MSG_NO_PRESENTE).
 */
mrf24_state_t MRF24TransmitirDato(mrf24_data_out_t * p_info_out_s);

/**
 * @brief  Se levantó la bandera indicando la llegada de un mensaje?
 *
 * @param  None.
 * @return mrf24_state_t Estado de la operación (ERROR_INESPERADO, MSG_PRESENTE,
 *         MSG_NO_PRESENTE).
 */
mrf24_state_t MRF24IsNewMsg(void);

/**
 * @brief  Recibir un paquete y dejarlo en el bufer de entrada en la estructura
 *         data_in_s.
 *
 * @param  None.
 * @return mrf24_state_t Estado de la operación (OPERACION_NO_REALIZADA, MSG_LEIDO).
 */
mrf24_state_t MRF24ReciboPaquete(void);

/**
 * @brief  Devuelvo el puntero a la estructura que contiene la información del
 *         mensaje de entrada.
 *
 * @param  None.
 * @return mrf24_data_in_t * Puntero a la estructura donde se almacena el mensaje
 *                           de llegada junto con la información del mismo.
 */
mrf24_data_in_t * MRF24GetDataIn(void);

mrf24_state_t MRF24BuscarDispositivos(void);
mrf24_state_t MRF24TransmitirDatoEncriptado(void);

#endif /* INC_DRV_MRF24J40_H_ */
