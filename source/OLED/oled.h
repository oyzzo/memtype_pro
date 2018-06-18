/*!  \file     i2c.h
 *   \brief    I2C Low Level Driver for SAMD
 *   Created:  15/06/2018
 *   Author:   MBorregoTrujillo
 */
#ifndef OLED_H_
#define OLED_H_

#include "sam.h"
#include "oled_cfg.h"

/* Prototypes */
void oled_init(void);
void oled_write_display(const uint8_t *data, uint16_t len);

#endif /* OLED_H_ */
