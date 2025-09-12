#include "unity.h"
#include "drv_MRF24J40.h"
#include "drv_MRF24J40_registers.h"
#include "mock_app_delay_unlock.h"
#include "mock_drv_MRF24J40_port.h"

extern mrf24_state_t SetShortAddr(uint8_t reg_address, uint8_t valor);
extern mrf24_state_t GetShortAddr(uint8_t reg_address, uint8_t * respuesta);
extern mrf24_state_t SetLongAddr(uint16_t reg_address, uint8_t valor);
extern mrf24_state_t GetLongAddr(uint16_t reg_address, uint8_t * respuesta);
extern mrf24_state_t ApplyDeviceAddress(void);
extern mrf24_state_t ApplyChannel(void);

void setUp(void) {
}

void tearDown(void) {
}

// comprobar que se envía una direccion de 1 byte  y un dato por SPI
void test_comprobar_que_se_envia_una_direccionde_1_byte_y_un_dato_por_SPI(void) {

    uint8_t reg = 0x00;
    uint8_t val = 0x20;
    uint8_t reg_address = (reg << 0x01) | 0x01;
    // Secuencia esperada
    SetCSPin_Expect(false);
    WriteByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    WriteByteSPIPort_ExpectAndReturn(&val, SPI_COMM_OK);
    SetCSPin_Expect(true);
    SetShortAddr(reg, val);
}

// comprobar que se lee un valor al consultar una direccion de 1 byte por SPI
void test_comprobar_que_se_lee_un_valor_al_consultar_una_direccionde_1_byte_por_SPI(void) {

    uint8_t reg = 0x05;
    uint8_t valor_esperado = 0xAB;
    uint8_t reg_address = (reg << 0x01) & 0x7E;
    uint8_t resultado = 0;
    // Secuencia esperada
    SetCSPin_Expect(false);
    WriteByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    ReadByteSPIPort_ExpectAndReturn(&resultado, SPI_COMM_OK);
    ReadByteSPIPort_ReturnThruPtr_respuesta(&valor_esperado);
    SetCSPin_Expect(true);
    GetShortAddr(reg, &resultado);
    TEST_ASSERT_EQUAL_HEX8(valor_esperado, resultado);
}

// comprobar que se envía una direccion de 2 bytes  y un dato por SPI
void test_comprobar_que_se_envia_una_direccionde_2_bytes_y_un_dato_por_SPI(void) {

    uint16_t reg = 0x0502;
    uint8_t val = 0x11;
    uint16_t reg_address = (reg << 0x05) | 0X8010;
    // Secuencia esperada
    SetCSPin_Expect(false);
    Write2ByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    WriteByteSPIPort_ExpectAndReturn(&val, SPI_COMM_OK);
    SetCSPin_Expect(true);
    SetLongAddr(reg, val);
}

// comprobar que se lee un valor al consultar una direccion de 2 bytes por SPI
void test_comprobar_que_se_lee_un_valor_al_consultar_una_direccionde_2_bytes_por_SPI(void) {

    uint16_t reg = 0x0125;
    uint8_t valor_esperado = 0x45;
    uint16_t reg_address = (reg << 0x05) | 0x8000;
    uint8_t resultado = 0;
    // Secuencia esperada
    SetCSPin_Expect(false);
    Write2ByteSPIPort_ExpectAndReturn(&reg_address, SPI_COMM_OK);
    ReadByteSPIPort_ExpectAndReturn(&resultado, SPI_COMM_OK);
    ReadByteSPIPort_ReturnThruPtr_respuesta(&valor_esperado);
    SetCSPin_Expect(true);
    GetLongAddr(reg, &resultado);
    TEST_ASSERT_EQUAL_HEX8(valor_esperado, resultado);
}

// probar de setear un canal de transmision y que la operacion se realice
void test_probar_de_setear_un_canal_de_transmision_y_que_la_operacion_se_realice(void) {

    mrf24_state_t respuesta = MRF24SetChannel(CH_11);
    TEST_ASSERT_EQUAL(OPERATION_OK, respuesta);
}

// probar de setear un canal de transmision fuera del rango y comprobar que devuelve un error
void test_probar_de_setear_un_canal_de_transmision_fuera_del_rango_y_comprobar_que_devuelve_un_error(
    void) {

    mrf24_state_t respuesta = MRF24SetChannel(0x02);
    TEST_ASSERT_EQUAL(INVALID_VALUE, respuesta);
}

// probar de actualizar la configuracion del canal en el dispositivo y comprobar que no hay errores
void test_probar_de_actualizar_la_configuracion_del_canal_en_el_dispositivo_y_comprobar_que_no_hay_errores(
    void) {

    ApplyChannel();
}
