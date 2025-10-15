/**
 *********************************************************************************
 * @file    drv_MRF24J40.c
 * @author  Lcdo. Mariano Ariel Deville
 * @brief   Implementación driver módulo MRF24J40
 * @version 0.1
 * @date 2025/02/01
 *********************************************************************************
 */

/* === Archivos cabecera ====================================================== */
#include <string.h>
#include <stdio.h>
#include "drv_MRF24J40.h"
#include "drv_MRF24J40_registers.h"
#include "drv_MRF24J40_port.h"
#include "app_delay_unlock.h"

/* === Definición de macros privadas ========================================== */
#define MRF_TIME_OUT     200
#define WAIT_1_MS        1
#define WAIT_50_MS       50
#define ENABLE           true
#define DISABLE          false
#define HEAD_LENGTH      (0X0B)
#define WRITE_16_BITS    (0X8010)
#define READ_16_BITS     (0X8000)
#define WRITE_8_BITS     (0x01)
#define READ_8_BITS      (0x7E)
#define SHIFT_LONG_ADDR  (0X05)
#define SHIFT_SHORT_ADDR (0X01)
#define SHIFT_BYTE       (0X08)
#define FCS_LQI_RSSI     (0x04)

/**
 * @brief Definiciones de la configuración por defecto.
 */
#define DEFAULT_CHANNEL    CH_11
#define DEFAULT_SEC_NUMBER (0X01)
#define MY_DEFAULT_PAN_ID  (0x9999)
#define MY_DEFAULT_ADDRESS (0xFFFE)

/* === Definición de variables privadas ======================================= */
mrf24_state_t estadoActual = INIT_FAIL;
static mrf24_data_config_t data_config_s = {0};
static mrf24_data_out_t data_out_s = {0};
static mrf24_data_in_t data_in_s = {0};

/**
 * @brief MAC address por defecto del dispositivo.
 */
static const uint8_t default_mac_address[] = {0x11, 0x28, 0x35, 0x44, 0x56, 0x66, 0x77, 0x01};

/**
 * @brief Security key por defecto del dispositivo.
 */
static const uint8_t default_security_key[] = {0x00, 0x10, 0x25, 0x37, 0x04, 0x55, 0x06, 0x79,
                                               0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15};

/* === Declaración de funciones privadas ====================================== */
void InicializoVariables(void);
mrf24_state_t InicializoMRF24(void);
mrf24_state_t SetShortAddr(uint8_t reg_address, uint8_t valor);
mrf24_state_t GetShortAddr(uint8_t reg_address, uint8_t * respuesta);
mrf24_state_t SetLongAddr(uint16_t reg_address, uint8_t valor);
mrf24_state_t GetLongAddr(uint16_t reg_address, uint8_t * respuesta);
mrf24_state_t ApplyDeviceAddress(void);
mrf24_state_t ApplyChannel(void);
mrf24_state_t ApplyDeviceMACAddress(void);

/* === Implementación de funciones privadas =================================== */
/**
 * @brief  Inicialización de variables de configuración.
 *
 * @param  None.
 * @return None.
 *
 * @note   Si no se inicializa previamente las variables se carga la configuración
 * 		   por defecto de fábrica.
 */
void InicializoVariables(void) {

    if (VACIO == data_config_s.channel) {

        memcpy(data_config_s.security_key, default_security_key, SEC_KEY_SIZE);
        memcpy(data_config_s.mac, default_mac_address, LARGE_MAC_SIZE);
        data_config_s.sequence_number = DEFAULT_SEC_NUMBER;
        data_config_s.channel = DEFAULT_CHANNEL;
        data_config_s.panid = MY_DEFAULT_PAN_ID;
        data_config_s.address = MY_DEFAULT_ADDRESS;
    }
    return;
}

/**
 * @brief  Inicialización del módulo MRF24J40MA.
 *
 * @param  None.
 * @return mrf24_state_t Estado de la operación (TIME_OUT_OCURRIDO, INICIALIZACION_OK).
 */
mrf24_state_t InicializoMRF24(void) {

    uint8_t lectura;
    delayNoBloqueanteData_t delay_time_out;
    DelayInit(&delay_time_out, MRF_TIME_OUT);
    SetShortAddr(SOFTRST, RSTPWR | RSTBB | RSTMAC);
    DelayReset(&delay_time_out);

    do {

        GetShortAddr(SOFTRST, &lectura);
        if (DelayRead(&delay_time_out))
            return TIME_OUT_OCURRED;
    } while (VACIO != (lectura & (RSTPWR | RSTBB | RSTMAC)));
    delay_t(WAIT_50_MS);
    SetShortAddr(RXFLUSH, RXFLUSH_RESET);
    ApplyDeviceAddress();
    ApplyDeviceMACAddress();
    SetLongAddr(RFCON1, VCOOPT1 | VCOOPT0);
    SetLongAddr(RFCON2, PLLEN);
    SetLongAddr(RFCON3, P20dBm | P0dBm);
    SetLongAddr(RFCON6, TXFIL | _20MRECVR);
    SetLongAddr(RFCON7, SLPCLK100KHZ);
    SetLongAddr(RFCON8, RFVCO);
    SetLongAddr(SLPCON1, CLKOUTDIS | SLPCLKDIV0);
    SetShortAddr(BBREG2, CCA_MODE_1);
    SetShortAddr(BBREG6, RSSIMODE2);
    SetShortAddr(CCAEDTH, CCAEDTH2 | CCAEDTH1);
    SetShortAddr(PACON2, FIFOEN | TXONTS2 | TXONTS1);
    SetShortAddr(TXSTBL, RFSTBL3 | RFSTBL0 | MSIFS2 | MSIFS0);
    DelayReset(&delay_time_out);

    do {

        GetLongAddr(RFSTATE, &lectura);
        lectura &= RX;
        if (DelayRead(&delay_time_out))
            return TIME_OUT_OCURRED;
    } while (RX != lectura);
    SetShortAddr(MRFINTCON,
                 SLPIE_DIS | WAKEIE_DIS | HSYMTMRIE_DIS | SECIE_DIS | TXG2IE_DIS | TXNIE_DIS);
    SetShortAddr(ACKTMOUT, DRPACK | MAWD5 | MAWD4 | MAWD3 | MAWD0);
    ApplyChannel();
    SetShortAddr(RXMCR, VACIO);
    GetShortAddr(INTSTAT, &lectura);
    return INIT_OK;
}

/**
 * @brief  Escribo en módulo MRF24J40 mediante SPI un registro de 1 byte y un
 *         dato de 1 byte.
 *
 * @param  uint8_t Dirección del registro.
 * @param  uint8_t Dato a enviar.
 * @return mrf24_state_t Estado de la operación (OPERATION_OK, OPERATION_FAIL).
 *
 * @note   Al escribir direcciones cortas (SHORT ADDRESS REGISTER) se comienza
 *         con el MSB en 0 indicando una dirección corta, 6 bits con la
 *         dirección del registro, y 1 bit indicando la lectura o escritura.
 */
mrf24_state_t SetShortAddr(uint8_t reg_address, uint8_t valor) {

    mrf24_state_t estado = OPERATION_OK;
    reg_address = (uint8_t)(reg_address << SHIFT_SHORT_ADDR) | WRITE_8_BITS;
    SetCSPin(DISABLE);
    if (SPI_COMM_ERROR == WriteByteSPIPort(&reg_address))
        estado = OPERATION_FAIL;
    if (SPI_COMM_ERROR == WriteByteSPIPort(&valor))
        estado = OPERATION_FAIL;
    SetCSPin(ENABLE);
    return estado;
}

/**
 * @brief  Leo en registro de 1 byte un dato de 1 byte.
 *
 * @param  Dirección del registro - 1 byte
 * @param  uint8_t * Puntero a la variable donde se guardará el dato leído.
 * @return mrf24_state_t Estado de la operación (OPERATION_OK, OPERATION_FAIL, INVALID_VALUE).
 *
 * @note   Al escribir direcciones cortas (SHORT ADDRESS REGISTER) se comienza
 *         con el MSB en 0 indicando una dirección corta, 6 bits con la
 *         dirección del registro, y 1 bit indicando la lectura o escritura.
 */
mrf24_state_t GetShortAddr(uint8_t reg_address, uint8_t * respuesta) {

    if (NULL == respuesta)
        return INVALID_VALUE;
    mrf24_state_t estado = OPERATION_OK;
    reg_address = (uint8_t)(reg_address << SHIFT_SHORT_ADDR) & READ_8_BITS;
    SetCSPin(DISABLE);
    if (SPI_COMM_ERROR == WriteByteSPIPort(&reg_address))
        estado = OPERATION_FAIL;
    if (SPI_COMM_ERROR == ReadByteSPIPort(respuesta))
        estado = OPERATION_FAIL;
    SetCSPin(ENABLE);
    return estado;
}

/**
 * @brief  Escribo de en registro de 2 bytes un dato de 1 byte.
 *
 * @param  uint16_t Dirección del registro.
 * @return uint8_t Valor devuelto por el módulo.
 * @return mrf24_state_t Estado de la operación (OPERATION_OK, OPERATION_FAIL).
 *
 * @note   Al escribir direcciones largas (LONG ADDRESS REGISTER) se comienza
 *         con el MSB en 1 indicando una dirección larga, 10 bits con la
 *         dirección del registro, y 1 bit indicando la lectura o escritura. En
 *         los 4 bits restantes (LSB) no importa el valor.
 */
mrf24_state_t SetLongAddr(uint16_t reg_address, uint8_t valor) {

    mrf24_state_t estado = OPERATION_OK;
    reg_address = (reg_address << SHIFT_LONG_ADDR) | WRITE_16_BITS;
    SetCSPin(DISABLE);
    if (SPI_COMM_ERROR == Write2ByteSPIPort(&reg_address))
        estado = OPERATION_FAIL;
    if (SPI_COMM_ERROR == WriteByteSPIPort(&valor))
        estado = OPERATION_FAIL;
    SetCSPin(ENABLE);
    return estado;
}

/**
 * @brief  Leo en registro de 2 bytes un dato de 1 byte.
 *
 * @param  uint16_t Dirección del registro.
 * @param  uint8_t * Puntero a la variable donde se guardará el dato leído.
 * @return mrf24_state_t Estado de la operación (OPERATION_OK, OPERATION_FAIL, INVALID_VALUE).
 *
 * @note   Al escribir direcciones largas (LONG ADDRESS REGISTER) se comienza
 *         con el MSB en 1 indicando una dirección larga, 10 bits con la
 *         dirección del registro, y 1 bit indicando la lectura o escritura. En
 *         los 4 bits restantes (LSB) no importa el valor.
 */
mrf24_state_t GetLongAddr(uint16_t reg_address, uint8_t * respuesta) {

    if (NULL == respuesta)
        return INVALID_VALUE;
    mrf24_state_t estado = OPERATION_OK;
    reg_address = (reg_address << SHIFT_LONG_ADDR) | READ_16_BITS;
    SetCSPin(DISABLE);
    if (SPI_COMM_ERROR == Write2ByteSPIPort(&reg_address))
        estado = OPERATION_FAIL;
    if (SPI_COMM_ERROR == ReadByteSPIPort(respuesta))
        estado = OPERATION_FAIL;
    SetCSPin(ENABLE);
    return estado;
}

/**
 * @brief  Seteo en el módulo en canal guardado en mrf24_data_config.
 *
 * @param  None.
 * @return mrf24_state_t Estado de la operación (OPERATION_OK, OPERATION_FAIL).
 */
mrf24_state_t ApplyChannel(void) {

    if (OPERATION_FAIL == SetLongAddr(RFCON0, data_config_s.channel))
        return OPERATION_FAIL;
    if (OPERATION_FAIL == SetShortAddr(RFCTL, RFRST_HOLD))
        return OPERATION_FAIL;
    if (OPERATION_FAIL == SetShortAddr(RFCTL, VACIO))
        return OPERATION_FAIL;
    delay_t(WAIT_1_MS);
    return OPERATION_OK;
}

/**
 * @brief  Seteo en el módulo la dirección corta guardada en mrf24_data_config.
 *
 * @param  None.
 * @return mrf24_state_t Estado de la operación (OPERATION_OK, OPERATION_FAIL).
 */
mrf24_state_t ApplyDeviceAddress(void) {

    if (OPERATION_FAIL == SetShortAddr(SADRH, (uint8_t)(data_config_s.address >> SHIFT_BYTE)))
        return OPERATION_FAIL;
    if (OPERATION_FAIL == SetShortAddr(SADRL, (uint8_t)(data_config_s.address)))
        return OPERATION_FAIL;
    if (OPERATION_FAIL == SetShortAddr(PANIDH, (uint8_t)(data_config_s.panid >> SHIFT_BYTE)))
        return OPERATION_FAIL;
    if (OPERATION_FAIL == SetShortAddr(PANIDL, (uint8_t)(data_config_s.panid)))
        return OPERATION_FAIL;
    return OPERATION_OK;
}

/**
 * @brief  Seteo en el módulo la dirección mac guardada en mrf24_data_config.
 *
 * @param  None.
 * @return mrf24_state_t Estado de la operación (OPERATION_OK, OPERATION_FAIL).
 */
mrf24_state_t ApplyDeviceMACAddress(void) {

    for (uint8_t i = 0; i < LARGE_MAC_SIZE; i++) {

        if (OPERATION_FAIL == SetShortAddr(EADR0 + i, data_config_s.mac[i]))
            return OPERATION_FAIL;
    }
    return OPERATION_OK;
}

/* === Implementación de funciones públicas =================================== */
mrf24_state_t MRF24J40Init(void) {

    InicializoVariables();
    InicializoPines();
    delay_t(WAIT_1_MS);
    SetResetPin(1);
    delay_t(WAIT_1_MS);
    estadoActual = InicializoMRF24();
    return estadoActual;
}

mrf24_state_t MRF24SetChannel(channel_list_t ch) {

    if (CH_11 > ch || CH_26 < ch)
        return INVALID_VALUE;
    data_config_s.channel = ch;
    return OPERATION_OK;
}

mrf24_state_t MRF24SetPanId(uint16_t pan_id) {

    if (BROADCAST == pan_id)
        return INVALID_VALUE;
    data_config_s.panid = pan_id;
    return OPERATION_OK;
}

mrf24_state_t MRF24SetAdd(uint16_t add) {

    if (BROADCAST == add)
        return INVALID_VALUE;
    data_config_s.address = add;
    return OPERATION_OK;
}

mrf24_state_t MRF24SetSec(uint16_t sec) {

    data_config_s.sequence_number = sec;
    return OPERATION_OK;
}

mrf24_state_t MRF24SetMAC(uint8_t mac[8]) {

    bool_t dif_cero = false;

    for (uint8_t i = 0; i < LARGE_MAC_SIZE; i++) {

        if (VACIO != mac[i]) {

            dif_cero = true;
            break;
        }
    }

    if (!dif_cero)
        return INVALID_VALUE;
    memcpy(data_config_s.mac, mac, sizeof(data_config_s.mac));
    return OPERATION_OK;
}

mrf24_state_t MRF24SetSecurityKey(uint8_t security_key[16]) {

    bool_t dif_cero = false;

    for (uint8_t i = 0; i < SEC_KEY_SIZE; i++) {

        if (VACIO != security_key[i]) {

            dif_cero = true;
            break;
        }
    }

    if (!dif_cero)
        return INVALID_VALUE;
    memcpy(data_config_s.security_key, security_key, sizeof(data_config_s.security_key));
    return OPERATION_OK;
}

mrf24_state_t MRF24TransmitirDato(mrf24_data_out_t * p_info_out_s) {

    if (INIT_OK != estadoActual)
        return OPERATION_FAIL;

    if (VACIO == p_info_out_s->dest_address)
        return DIRECTION_EMPTY;

    if (VACIO == p_info_out_s->buffer_size)
        return BUFFER_EMPTY;

    if (BUFFER_SIZE < p_info_out_s->buffer_size)
        return TO_LONG_MSG;
    uint8_t pos_mem = 0;
    SetLongAddr(pos_mem++, HEAD_LENGTH);
    SetLongAddr(pos_mem++, p_info_out_s->buffer_size + HEAD_LENGTH);
    SetLongAddr(pos_mem++, DATA | ACK_REQ | INTRA_PAN); // LSB.
    SetLongAddr(pos_mem++, SHORT_S_ADD | SHORT_D_ADD);  // MSB.
    SetLongAddr(pos_mem++, data_config_s.sequence_number++);

    if (VACIO == p_info_out_s->dest_panid)
        p_info_out_s->dest_panid = data_config_s.panid;
    SetLongAddr(pos_mem++, (uint8_t)p_info_out_s->dest_panid);
    SetLongAddr(pos_mem++, (uint8_t)(p_info_out_s->dest_panid >> SHIFT_BYTE));
    SetLongAddr(pos_mem++, (uint8_t)p_info_out_s->dest_address);
    SetLongAddr(pos_mem++, (uint8_t)(p_info_out_s->dest_address >> SHIFT_BYTE));

    if (VACIO == p_info_out_s->origin_address)
        p_info_out_s->origin_address = data_config_s.address;
    SetLongAddr(pos_mem++, (uint8_t)p_info_out_s->origin_address);
    SetLongAddr(pos_mem++, (uint8_t)(p_info_out_s->origin_address >> SHIFT_BYTE));

    for (int8_t i = 0; i < p_info_out_s->buffer_size; i++) {

        SetLongAddr(pos_mem++, p_info_out_s->buffer[i]);
    }
    SetLongAddr(pos_mem++, VACIO);
    SetShortAddr(TXNCON, TXNACKREQ | TXNTRIG);
    return TRANS_COMPLETED;
}

mrf24_state_t MRF24IsNewMsg(void) {

    if (INIT_OK != estadoActual)
        return UNEXPECTED_ERROR;

    if (IsMRF24Interrup())
        return MSG_PRESENT;
    return BUFFER_EMPTY;
}

mrf24_state_t MRF24ReciboPaquete(void) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*
     * agregar la lectura del rssi y del lq, vienen en el paquete del mensaje.
     */

    if (INIT_OK != estadoActual)
        return OPERATION_FAIL;
    SetLongAddr(BBREG1, RXDECINV);
    SetShortAddr(RXFLUSH, DATAONLY);
    GetLongAddr(RX_FIFO, &data_in_s.buffer_size);
    uint8_t add = VACIO;
    GetLongAddr(RX_FIFO + 9, &add);
    data_in_s.address = (uint16_t)(add << SHIFT_BYTE);
    GetLongAddr(RX_FIFO + 8, &add);
    data_in_s.address |= (uint16_t)add;

    for (uint8_t i = 0; i < data_in_s.buffer_size - FCS_LQI_RSSI; i++) {

        GetLongAddr(RX_FIFO + HEAD_LENGTH + i - 1, &data_in_s.buffer[i]);
    }
    SetLongAddr(BBREG1, VACIO);
    GetShortAddr(INTSTAT, &add);
    return MSG_READ;
}

mrf24_data_in_t * MRF24GetDataIn(void) {

    return &data_in_s;
}

mrf24_state_t MRF24BuscarDispositivos(void) {

    //   static MRF24_discover_nearby_t algo[10];

    if (INIT_OK != estadoActual)
        return OPERATION_FAIL;

    data_out_s.dest_address = 1;

    SetShortAddr(TXNCON, TXNACKREQ | TXNTRIG);

    return MSG_READ;
}
