/*!  \file     usart.h
 *   \brief    USART Low Level Driver for SAMD
 *   Created:  15/06/2018
 *   Author:   MBorregoTrujillo
 */
#ifndef USART_H_
#define USART_H_

#include "sam.h"

/** USART RX pad allocation */
typedef enum {
    USART_RX_PAD0 = 0,
    USART_RX_PAD1 = 1,
    USART_RX_PAD2 = 2,
    USART_RX_PAD3 = 3
} usart_rx_pad_te;

/** USART TX,XCK or TX,RTS,CTS pad allocation */
typedef enum {
    USART_TX_P0_XCK_P1 = 0,
    USART_TX_P2_XCK_P3 = 1,
    USART_TX_P0_RTS_P2_CTS_P3 = 2
} usart_tx_xck_rts_cts_pad_te;

/* Prototypes */
void usart_deinit(Sercom* pt);
void usart_init(Sercom* pt,
                       uint32_t baud_div,
                       usart_rx_pad_te rx_pad,
                       usart_tx_xck_rts_cts_pad_te usart_tx_xck_rts_cts_pad);
uint8_t usart_write_byte(Sercom* pt, uint8_t data);

#endif /* USART_H_ */
