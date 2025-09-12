/**
 *******************************************************************************
 * @file    drv_MRF24J40_registers.h
 * @author  Lcdo. Mariano Ariel Deville
 * @brief	Archivo cabecera para el archivo drv_MRF24J40.c
 *******************************************************************************
 * @attention Driver independiente de la plataforma de uso y del compilardor.
 *
 *******************************************************************************
 */
#ifndef XC_HEADER_TEMPLATE_H
#define XC_HEADER_TEMPLATE_H

enum {

    EADR0 = 0x05,
    EADR1,
    EADR2,
    EADR3,
    EADR4,
    EADR5,
    EADR6,
    EADR7
} long_mac_address_e;

/* Direcciones de los registros de 8 bits ------------------------------------*/
#define RXMCR     (0x00)
#define PANIDL    (0x01)
#define PANIDH    (0x02)
#define SADRL     (0x03)
#define SADRH     (0x04)
#define RXFLUSH   (0x0D)
#define ORDER     (0x10)
#define TXMCR     (0x11)
#define ACKTMOUT  (0x12)
#define ESLOTG1   (0x13)
#define SYMTICKL  (0x14)
#define SYMTICKH  (0x15)
#define PACON0    (0x16)
#define PACON1    (0x17)
#define PACON2    (0x18)
#define TXBCON0   (0x1A)
#define TXNCON    (0x1B)
#define TXG1CON   (0x1C)
#define TXG2CON   (0x1D)
#define ESLOTG23  (0x1E)
#define ESLOTG45  (0x1F)
#define ESLOTG67  (0x20)
#define TXPEND    (0x21)
#define WAKECON   (0x22)
#define FRMOFFSET (0x23)
#define TXSTAT    (0x24)
#define TXBCON1   (0x25)
#define GATECLK   (0x26)
#define TXTIME    (0x27)
#define HSYMTMRL  (0x28)
#define HSYMTMRH  (0x29)
#define SOFTRST   (0x2A)
#define SECCON0   (0x2C)
#define SECCON1   (0x2D)
#define TXSTBL    (0x2E)
#define RXSR      (0x30)
#define INTSTAT   (0x31)
#define MRFINTCON (0x32)
#define GPIO      (0x33)
#define TRISGPIO  (0x34)
#define SLPACK    (0x35)
#define RFCTL     (0x36)
#define SECCR2    (0x37)
#define BBREG0    (0x38)
#define BBREG1    (0x39)
#define BBREG2    (0x3A)
#define BBREG3    (0x3B)
#define BBREG4    (0x3C)
#define BBREG6    (0x3E)
#define CCAEDTH   (0x3F)

/* Direcciones de los registros de 16 bits -----------------------------------*/
#define RFCON0    (0x200)
#define RFCON1    (0x201)
#define RFCON2    (0x202)
#define RFCON3    (0x203)
#define RFCON5    (0x205)
#define RFCON6    (0x206)
#define RFCON7    (0x207)
#define RFCON8    (0x208)
#define SLPCAL0   (0x209)
#define SLPCAL1   (0x20a)
#define SLPCAL2   (0x20b)
#define RFSTATE   (0x20f)
#define RSSI      (0x210)
#define SLPCON0   (0x211)
#define SLPCON1   (0x220)
#define WAKETIMEL (0x222)
#define WAKETIMEH (0x223)
#define REMCNTL   (0x224)
#define REMCNTH   (0x225)
#define MAINCNT0  (0x226)
#define MAINCNT1  (0x227)
#define MAINCNT2  (0x228)
#define MAINCNT3  (0x229)
#define TESTMODE  (0x22f)
#define ASSOEADR0 (0x230)
#define ASSOEADR1 (0x231)
#define ASSOEADR2 (0x232)
#define ASSOEADR3 (0x233)
#define ASSOEADR4 (0x234)
#define ASSOEADR5 (0x235)
#define ASSOEADR6 (0x236)
#define ASSOEADR7 (0x237)
#define ASSOSADR0 (0x238)
#define ASSOSADR1 (0x239)

/* Direcciones de los registros de las FIFOs ---------------------------------*/
#define TX_NORMAL_FIFO (0x000)
#define TX_BEACON_FIFO (0x080)
#define TX_GTS1_FIFO   (0x100)
#define TX_GTS2_FIFO   (0x180)
#define RX_FIFO        (0x300)
#define TX_SEC_KEY     (0x280)
#define RX_SEC_KEY     (0x2B0)

/* Definiciones del registro RXMCR -------------------------------------------*/
#define NOACKRSP (0X20)
#define PANCOORD (0X08)
#define COORD    (0X04)
#define ERRPKT   (0X02)
#define PROMI    (0X01)

/* Definiciones del registro RXFLUSH -----------------------------------------*/
#define WAKEPOL_HIGH  (0X40)
#define WAKEPAD_EN    (0X20)
#define CMDONLY       (0X08)
#define DATAONLY      (0X04)
#define BCNONLY       (0X02)
#define RXFLUSH_RESET (0X01)

/* Definiciones del registro TXMCR -------------------------------------------*/
#define NOCSMA    (0X80)
#define BATLIFEXT (0X40)
#define SLOTTED   (0X20)
#define MACMINBE1 (0X10)
#define MACMINBE0 (0X08)
#define CSMABF2   (0X04)
#define CSMABF1   (0X02)
#define CSMABF0   (0X01)

/* Definiciones del registro ACKTMOUT -----------------------------------------*/
#define DRPACK (0X80)
#define MAWD6  (0X40)
#define MAWD5  (0X20)
#define MAWD4  (0X10)
#define MAWD3  (0X08)
#define MAWD2  (0X04)
#define MAWD1  (0X02)
#define MAWD0  (0X01)

/* Definiciones del registro TXBCON0 -----------------------------------------*/
#define TXBSECEN (0X02)
#define TXBTRIG  (0X01)

/* Definiciones del registro TXNCON ------------------------------------------*/
#define FPSTAT    (0X10)
#define INDIRECT  (0X08)
#define TXNACKREQ (0X04)
#define TXNSECEN  (0X02)
#define TXNTRIG   (0X01)

/* Definiciones del registro WAKECON -----------------------------------------*/
#define IMMWAKE (0X80)
#define REGWAKE (0X40)

/* Definiciones del registro TXBCON1 -----------------------------------------*/
#define TXBMSK     (0X80)
#define WU_BCN     (0X40)
#define RSSI_8_SYM (0X30)
#define RSSI_4_SYM (0X20)
#define RSSI_2_SYM (0X10)
#define RSSI_1_SYM (0X00)

/* Definiciones del registro GATECLK -----------------------------------------*/
#define GTSON (0X08)

/* Definiciones del registro SOFTRST -----------------------------------------*/
#define RSTPWR (0X04)
#define RSTBB  (0X02)
#define RSTMAC (0X01)

/* Definiciones del registro SECCON0 -----------------------------------------*/
#define SECIGNORE      (0X80)
#define SECSTART       (0X40)
#define RX_AES_CBC_32  (0X38)
#define RX_AES_CBC_64  (0X30)
#define RX_AES_CBC_128 (0X28)
#define RX_AES_CCM_32  (0X20)
#define RX_AES_CCM_64  (0X18)
#define RX_AES_CCM_128 (0X10)
#define RX_AES_CTR     (0X08)
#define TX_AES_CBC_32  (0X07)
#define TX_AES_CBC_64  (0X06)
#define TX_AES_CBC_128 (0X05)
#define TX_AES_CCM_32  (0X04)
#define TX_AES_CCM_64  (0X03)
#define TX_AES_CCM_128 (0X02)
#define TX_AES_CTR     (0X01)

/* Definiciones del registro SECCON1 -----------------------------------------*/
#define TXB_AES_CBC_32  (0X70)
#define TXB_AES_CBC_64  (0X60)
#define TXB_AES_CBC_128 (0X50)
#define TXB_AES_CCM_32  (0X40)
#define TXB_AES_CCM_64  (0X30)
#define TXB_AES_CCM_128 (0X20)
#define TXB_AES_CTR     (0X10)

/* Definiciones del registro PACON2 ------------------------------------------*/
#define FIFOEN  (0X80)
#define TXONTS3 (0X20)
#define TXONTS2 (0X10)
#define TXONTS1 (0X08)
#define TXONTS0 (0X04)
#define TXONT8  (0X02)
#define TXONT7  (0X01)

/* Definiciones del registro TXSTBL ------------------------------------------*/
#define RFSTBL3 (0X80)
#define RFSTBL2 (0X40)
#define RFSTBL1 (0X20)
#define RFSTBL0 (0X10)
#define MSIFS3  (0X08)
#define MSIFS2  (0X04)
#define MSIFS1  (0X02)
#define MSIFS0  (0X01)

/* Definiciones del registro RXSR --------------------------------------------*/
#define UPSECERR  (0X40)
#define BATIND    (0X20)
#define SECDECERR (0X04)

/* Definiciones del registro INTSTAT -----------------------------------------*/
#define SLPIF     (0X80)
#define WAKEIF    (0X40)
#define HSYMTMRIF (0X20)
#define SECIF     (0X10)
#define RXIF      (0X08)
#define TXG2IF    (0X04)
#define TXG1IF    (0X02)
#define TXNIF     (0X01)

/* Definiciones del registro INTCON ------------------------------------------*/
#define SLPIE_DIS     (0X80)
#define WAKEIE_DIS    (0X40)
#define HSYMTMRIE_DIS (0X20)
#define SECIE_DIS     (0X10)
#define RXIE_DIS      (0X08)
#define TXG2IE_DIS    (0X04)
#define TXG1IE_DIS    (0X02)
#define TXNIE_DIS     (0X01)

/* Definiciones del registro RFCTL -------------------------------------------*/
#define WAKECNT8   (0X10)
#define WAKECNT7   (0X08)
#define RFRST_HOLD (0X04)
#define RFTXMODE   (0X02)
#define RFRXMODE   (0X01)

/* Definiciones del registro BBREG0 ------------------------------------------*/
#define TURBO (0X01)

/* Definiciones del registro BBREG1 ------------------------------------------*/
#define RXDECINV (0X04)

/* Definiciones del registro BBREG2 ------------------------------------------*/
#define CCA_MODE_3 (0XC0)
#define CCA_MODE_1 (0X80)
#define CCA_MODE_2 (0X40)
#define CCACSTH3   (0X20)
#define CCACSTH2   (0X10)
#define CCACSTH1   (0X08)
#define CCACSTH0   (0X04)

/* Definiciones del registro BBREG3 ------------------------------------------*/
#define IEEE_802_15_4 (0XD0)
#define TURBO_MODE    (0X30)
#define PREDETTH2     (0X08)
#define PREDETTH1     (0X04)
#define PREDETTH0     (0X02)

/* Definiciones del registro BBREG4 ------------------------------------------*/
#define IEEE_250KBPS  (0X80)
#define TURBO_625KBPS (0X40)
#define PRECNT2       (0X10)
#define PRECNT1       (0X08)
#define PRECNT0       (0X04)

/* Definiciones del registro BBREG6 ------------------------------------------*/
#define RSSIMODE1 (0X80)
#define RSSIMODE2 (0X40)

/* Definiciones del registro CCAEDTH -----------------------------------------*/
#define CCAEDTH7 (0X80)
#define CCAEDTH6 (0X40)
#define CCAEDTH5 (0X20)
#define CCAEDTH4 (0X10)
#define CCAEDTH3 (0X08)
#define CCAEDTH2 (0X04)
#define CCAEDTH1 (0X02)
#define CCAEDTH0 (0X01)

/* Definiciones del registro RFCON1 ------------------------------------------*/
#define VCOOPT7 (0X80)
#define VCOOPT6 (0X40)
#define VCOOPT5 (0X20)
#define VCOOPT4 (0X10)
#define VCOOPT3 (0X08)
#define VCOOPT2 (0X04)
#define VCOOPT1 (0X02)
#define VCOOPT0 (0X01)

/* Definiciones del registro TXSTAT ------------------------------------------*/
#define TXNRETRY1 (0X80)
#define TXNRETRY0 (0X40)
#define CCAFAIL   (0X20)
#define TXG2FNT   (0X10)
#define TXG1FNT   (0X08)
#define TXG2STAT  (0X04)
#define TXG1STAT  (0X02)
#define TXNSTAT   (0X01)

/* Definiciones del registro RFCON2 ------------------------------------------*/
#define PLLEN (0X80)

/* Definiciones del registro RFCON3 ------------------------------------------*/
#define P30dBm  (0XC0)
#define P20dBm  (0X80)
#define P10dBm  (0X40)
#define P6_3dBm (0X38)
#define P4_9dBm (0X30)
#define P3_7dBm (0X28)
#define P2_8dBm (0X20)
#define P1_9dBm (0X18)
#define P1_2dBm (0X10)
#define P0_5dBm (0X08)
#define P0dBm   (0X00)

/* Definiciones del registro RFCON5 ------------------------------------------*/
#define BATTH_3_5 (0XE0)
#define BATTH_3_3 (0XD0)
#define BATTH_3_2 (0XC0)
#define BATTH_3_1 (0XB0)
#define BATTH_2_8 (0XA0)
#define BATTH_2_7 (0X90)
#define BATTH_2_6 (0X80)
#define BATTH_2_5 (0X70)

/* Definiciones del registro RFCON6 ------------------------------------------*/
#define TXFIL     (0X80)
#define _20MRECVR (0X10)
#define BATEN     (0X08)

/* Definiciones del registro RFCON7 ------------------------------------------*/
#define SLPCLK100KHZ (0X80)
#define SLPCLK32KHZ  (0X40)

/* Definiciones del registro RFCON8 ------------------------------------------*/
#define RFVCO (0X10)

/* Definiciones del registro RFSTATE -----------------------------------------*/
#define RTSEL2   (0XE0)
#define RTSEL1   (0XC0)
#define RX       (0XA0)
#define TX       (0X80)
#define CALVCO   (0X60)
#define RF_SLEEP (0X40)
#define CALFIL   (0X20)
#define RF_RESET (0X00)

/* Definiciones del registro SLPCON0 -----------------------------------------*/
#define INTEDGE_RISISNG (0X02)
#define SLPCLKDIS       (0X01)

/* Definiciones del registro SLPCON1 -----------------------------------------*/
#define CLKOUTDIS  (0X20)
#define SLPCLKDIV4 (0X10)
#define SLPCLKDIV3 (0X08)
#define SLPCLKDIV2 (0X04)
#define SLPCLKDIV1 (0X02)
#define SLPCLKDIV0 (0X01)

/* Definiciones del registro TESTMODE ----------------------------------------*/
#define RSSIWAIT1 (0X10)
#define RSSIWAIT0 (0X08)
#define TESTMODE2 (0X04)
#define TESTMODE1 (0X02)
#define TESTMODE0 (0X01)

/* LSB */
#define DATA       (0X01)
#define ACK        (0X02)
#define MAC_COMM   (0X03)
#define SECURITY   (0X08)
#define FRAME_PEND (0X10)
#define ACK_REQ    (0X20)
#define INTRA_PAN  (0X40)

/* MSB */
#define TX_CTR        (0x01)
#define TX_CCM128     (0x02)
#define TX_CCM64      (0x03)
#define TX_CCM32      (0x04)
#define TX_CBC_MAC128 (0x05)
#define TX_CBC_MAC64  (0x06)
#define TX_CBC_MAC32  (0x07)
#define SHORT_D_ADD   (0X08)
#define LONG_D_ADD    (0X0C)
#define SHORT_S_ADD   (0X80)
#define LONG_S_ADD    (0XC0)

#endif /* XC_HEADER_TEMPLATE_H */
