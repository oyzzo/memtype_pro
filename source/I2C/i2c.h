/*!  \file     i2c.h
 *   \brief    I2C Low Level Driver for SAMD
 *   Created:  15/06/2018
 *   Author:   MBorregoTrujillo
 */
#ifndef I2C_H_
#define I2C_H_

#include "sam.h"

/* Prototypes */
void i2c_deinit(Sercom* sercom_pt);
void i2c_master_init(Sercom* sercom_pt, uint32_t baudrate);
void i2c_master_start(Sercom* sercom_pt, uint8_t addr);
void i2c_master_stop(Sercom* sercom_pt);
void i2c_master_write(Sercom* sercom_pt, uint8_t *data, uint8_t len);
void i2c_master_write_byte(Sercom* sercom_pt, uint8_t data);

#endif /* I2C_H_ */
