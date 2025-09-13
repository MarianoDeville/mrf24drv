#include "unity.h"
#include "drv_MRF24J40.h"
#include "drv_MRF24J40_registers.h"
#include "mock_app_delay_unlock.h"
#include "mock_drv_MRF24J40_port.h"

#define WRITE_16_BITS    (0X8010)
#define READ_16_BITS     (0X8000)
#define WRITE_8_BITS     (0x01)
#define READ_8_BITS      (0x7E)
#define SHIFT_LONG_ADDR  (0X05)
#define SHIFT_SHORT_ADDR (0X01)

extern mrf24_state_t SetShortAddr(uint8_t reg_address, uint8_t valor);
extern mrf24_state_t GetShortAddr(uint8_t reg_address, uint8_t * respuesta);
extern mrf24_state_t SetLongAddr(uint16_t reg_address, uint8_t valor);
extern mrf24_state_t GetLongAddr(uint16_t reg_address, uint8_t * respuesta);
extern mrf24_state_t ApplyDeviceAddress(void);
extern mrf24_state_t ApplyChannel(void);

void setUp(void) {

    MRF24SetChannel(CH_11);
}

void tearDown(void) {
}

uint8_t adaptarDireccionSPI8WriteShort(uint8_t reg_address) {

    return ((reg_address << SHIFT_SHORT_ADDR) | WRITE_8_BITS);
}

uint8_t adaptarDireccionSPI8ReadShort(uint8_t reg_address) {

    return ((reg_address << SHIFT_SHORT_ADDR) & READ_8_BITS);
}

uint16_t adaptarDireccionSPI16WriteLong(uint16_t reg_address) {

    return ((reg_address << SHIFT_LONG_ADDR) | WRITE_16_BITS);
}

uint16_t adaptarDireccionSPI16ReadLong(uint16_t reg_address) {

    return ((reg_address << SHIFT_LONG_ADDR) | READ_16_BITS);
}

// probar de setear un canal de transmision y que la operacion se realice sin errores
void test_probar_de_setear_un_canal_de_transmision_y_que_la_operacion_se_realice_sin_errores(void) {

    mrf24_state_t respuesta = MRF24SetChannel(CH_11);
    TEST_ASSERT_EQUAL(OPERATION_OK, respuesta);
}

// probar de setear un canal de transmision fuera de los rangos y comprobar que devuelve un error
void test_probar_de_setear_un_canal_de_transmision_fuera_de_los_rangos_y_comprobar_que_devuelve_un_error(
    void) {

    mrf24_state_t respuesta = MRF24SetChannel(CH_11 - 1);
    TEST_ASSERT_EQUAL(INVALID_VALUE, respuesta);

    respuesta = MRF24SetChannel(CH_26 + 1);
    TEST_ASSERT_EQUAL(INVALID_VALUE, respuesta);
}

// comprobar que se envía una direccion de 1 byte y un dato por SPI sin errores
void test_comprobar_que_se_envia_una_direccionde_1_byte_y_un_dato_por_SPI_sin_errores(void) {

    uint8_t reg = 0x03;
    uint8_t val = 0x20;
    uint8_t reg_address = adaptarDireccionSPI8WriteShort(reg);
    // Secuencia esperada
    SetCSPin_Expect(false);
    WriteByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    WriteByteSPIPort_ExpectAndReturn(&val, SPI_COMM_OK);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t respuesta = SetShortAddr(reg, val);
    TEST_ASSERT_EQUAL(OPERATION_OK, respuesta);
}

// comprobar que se envía una direccion de 1 byte y un dato por SPI con errores de comunicación
void test_comprobar_que_se_envia_una_direccionde_1_byte_y_un_dato_por_SPI_con_errores_de_comunicacion(
    void) {

    uint8_t reg = 0x00;
    uint8_t val = 0x20;
    uint8_t reg_address = adaptarDireccionSPI8WriteShort(reg);
    // Secuencia esperada
    SetCSPin_Expect(false);
    WriteByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_ERROR);
    WriteByteSPIPort_ExpectAndReturn(&val, SPI_COMM_OK);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t respuesta = SetShortAddr(reg, val);
    TEST_ASSERT_EQUAL(OPERATION_FAIL, respuesta);
}

// comprobar que se lee un valor al consultar una direccion de 1 byte por SPI sin errores
void test_comprobar_que_se_lee_un_valor_al_consultar_una_direccionde_1_byte_por_SPI_sin_errores(
    void) {

    uint8_t reg = 0x05;
    uint8_t valor_esperado = 0xAB;
    uint8_t reg_address = adaptarDireccionSPI8ReadShort(reg);
    uint8_t resultado;
    // Secuencia esperada
    SetCSPin_Expect(false);
    WriteByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    ReadByteSPIPort_ExpectAndReturn(&resultado, SPI_COMM_OK);
    ReadByteSPIPort_ReturnThruPtr_respuesta(&valor_esperado);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t respuesta = GetShortAddr(reg, &resultado);
    TEST_ASSERT_EQUAL_HEX8(valor_esperado, resultado);
    TEST_ASSERT_EQUAL(OPERATION_OK, respuesta);
}

// comprobar que se lee un valor al consultar una direccion de 1 byte por SPI con errores de
// comunicación 1
void test_comprobar_que_se_lee_un_valor_al_consultar_una_direccionde_1_byte_por_SPI_con_errores_de_comunicacion_1(
    void) {

    uint8_t reg = 0x15;
    uint8_t valor_esperado = 0x10;
    uint8_t reg_address = adaptarDireccionSPI8ReadShort(reg);
    uint8_t resultado;
    // Secuencia esperada
    SetCSPin_Expect(false);
    WriteByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_ERROR);
    ReadByteSPIPort_ExpectAndReturn(&resultado, SPI_COMM_OK);
    ReadByteSPIPort_ReturnThruPtr_respuesta(&valor_esperado);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t respuesta = GetShortAddr(reg, &resultado);
    TEST_ASSERT_EQUAL_HEX8(valor_esperado, resultado);
    TEST_ASSERT_EQUAL(OPERATION_FAIL, respuesta);
}

// comprobar que se lee un valor al consultar una direccion de 1 byte por SPI con errores de
// comunicación 2
void test_comprobar_que_se_lee_un_valor_al_consultar_una_direccionde_1_byte_por_SPI_con_errores_de_comunicacion_2(
    void) {

    uint8_t reg = 0x33;
    uint8_t valor_esperado = 0x51;
    uint8_t reg_address = adaptarDireccionSPI8ReadShort(reg);
    uint8_t resultado;
    // Secuencia esperada
    SetCSPin_Expect(false);
    WriteByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    ReadByteSPIPort_ExpectAndReturn(&resultado, SPI_COMM_ERROR);
    ReadByteSPIPort_ReturnThruPtr_respuesta(&valor_esperado);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t respuesta = GetShortAddr(reg, &resultado);
    TEST_ASSERT_EQUAL_HEX8(valor_esperado, resultado);
    TEST_ASSERT_EQUAL(OPERATION_FAIL, respuesta);
}

// comprobar que se lee un valor al consultar una direccion de 1 byte por SPI con error null pointer
void test_comprobar_que_se_lee_un_valor_al_consultar_una_direccionde_1_byte_por_SPI_con_error_null_pointer(
    void) {

    uint8_t reg = 0x33;
    // retorno esperado
    mrf24_state_t respuesta = GetShortAddr(reg, NULL);
    TEST_ASSERT_EQUAL(INVALID_VALUE, respuesta);
}

// comprobar que se envía una direccion de 2 bytes  y un dato por SPI sin errores
void test_comprobar_que_se_envia_una_direccionde_2_bytes_y_un_dato_por_SPI_sin_errores(void) {

    uint16_t reg = 0x0502;
    uint8_t val = 0x11;
    uint16_t reg_address = adaptarDireccionSPI16WriteLong(reg);
    // Secuencia esperada
    SetCSPin_Expect(false);
    Write2ByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    WriteByteSPIPort_ExpectAndReturn(&val, SPI_COMM_OK);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t estado = SetLongAddr(reg, val);
    TEST_ASSERT_EQUAL_HEX8(OPERATION_OK, estado);
}

// comprobar que se envía una direccion de 2 bytes  y un dato por SPI con errores de comunicacion 1
void test_comprobar_que_se_envia_una_direccionde_2_bytes_y_un_dato_por_SPI_con_errores_de_comunicacion_1(
    void) {

    uint16_t reg = 0x0505;
    uint8_t val = 0x13;
    uint16_t reg_address = adaptarDireccionSPI16WriteLong(reg);
    // Secuencia esperada
    SetCSPin_Expect(false);
    Write2ByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_ERROR);
    WriteByteSPIPort_ExpectAndReturn(&val, SPI_COMM_OK);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t estado = SetLongAddr(reg, val);
    TEST_ASSERT_EQUAL_HEX8(OPERATION_FAIL, estado);
}

// comprobar que se envía una direccion de 2 bytes  y un dato por SPI con errores de comunicacion 2
void test_comprobar_que_se_envia_una_direccionde_2_bytes_y_un_dato_por_SPI_con_errores_de_comunicacion_2(
    void) {

    uint16_t reg = 0x0f20;
    uint8_t val = 0x99;
    uint16_t reg_address = adaptarDireccionSPI16WriteLong(reg);
    // Secuencia esperada
    SetCSPin_Expect(false);
    Write2ByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    WriteByteSPIPort_ExpectAndReturn(&val, SPI_COMM_ERROR);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t estado = SetLongAddr(reg, val);
    TEST_ASSERT_EQUAL_HEX8(OPERATION_FAIL, estado);
}

// comprobar que se lee un valor al consultar una direccion de 2 bytes por SPI sin errores
void test_comprobar_que_se_lee_un_valor_al_consultar_una_direccionde_2_bytes_por_SPI_sin_errores(
    void) {

    uint16_t reg = 0x0125;
    uint8_t valor_esperado = 0x45;
    uint16_t reg_address = adaptarDireccionSPI16ReadLong(reg);
    uint8_t resultado = 0;
    // Secuencia esperada
    SetCSPin_Expect(false);
    Write2ByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    ReadByteSPIPort_ExpectAndReturn(&resultado, SPI_COMM_OK);
    ReadByteSPIPort_ReturnThruPtr_respuesta(&valor_esperado);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t estado = GetLongAddr(reg, &resultado);
    TEST_ASSERT_EQUAL_HEX8(valor_esperado, resultado);
    TEST_ASSERT_EQUAL_HEX8(OPERATION_OK, estado);
}

// comprobar que se lee un valor al consultar una direccion de 2 bytes por SPI con errores de
// comunicacion 1
void test_comprobar_que_se_lee_un_valor_al_consultar_una_direccionde_2_bytes_por_SPI_con_errores_de_comunicacion_1(
    void) {

    uint16_t reg = 0x0346;
    uint8_t valor_esperado = 0x88;
    uint16_t reg_address = adaptarDireccionSPI16ReadLong(reg);
    uint8_t resultado = 0;
    // Secuencia esperada
    SetCSPin_Expect(false);
    Write2ByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_ERROR);
    ReadByteSPIPort_ExpectAndReturn(&resultado, SPI_COMM_OK);
    ReadByteSPIPort_ReturnThruPtr_respuesta(&valor_esperado);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t estado = GetLongAddr(reg, &resultado);
    TEST_ASSERT_EQUAL_HEX8(valor_esperado, resultado);
    TEST_ASSERT_EQUAL_HEX8(OPERATION_FAIL, estado);
}

// comprobar que se lee un valor al consultar una direccion de 2 bytes por SPI con errores de
// comunicacion 2
void test_comprobar_que_se_lee_un_valor_al_consultar_una_direccionde_2_bytes_por_SPI_con_errores_de_comunicacion_2(
    void) {

    uint16_t reg = 0x0222;
    uint8_t valor_esperado = 0x65;
    uint16_t reg_address = adaptarDireccionSPI16ReadLong(reg);
    uint8_t resultado = 0;
    // Secuencia esperada
    SetCSPin_Expect(false);
    Write2ByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    ReadByteSPIPort_ExpectAndReturn(&resultado, SPI_COMM_ERROR);
    ReadByteSPIPort_ReturnThruPtr_respuesta(&valor_esperado);
    SetCSPin_Expect(true);
    // retorno esperado
    mrf24_state_t estado = GetLongAddr(reg, &resultado);
    TEST_ASSERT_EQUAL_HEX8(valor_esperado, resultado);
    TEST_ASSERT_EQUAL_HEX8(OPERATION_FAIL, estado);
}

// comprobar que se lee un valor al consultar una direccion de 2 bytes por SPI con error null
// pointer
void test_comprobar_que_se_lee_un_valor_al_consultar_una_direccionde_2_bytes_por_SPI_con_error_null_pointer(
    void) {

    uint16_t reg = 0x0222;
    // retorno esperado
    mrf24_state_t estado = GetLongAddr(reg, NULL);
    TEST_ASSERT_EQUAL_HEX8(INVALID_VALUE, estado);
}

// probar que ApplyChannel devuelve FAIL si SetLongAddr falla
void test_ApplyChannel_devuelve_fail_si_SetLongAddr_falla(void) {

    mrf24_state_t respuesta = ApplyChannel();
    TEST_ASSERT_EQUAL(OPERATION_FAIL, respuesta);
}
