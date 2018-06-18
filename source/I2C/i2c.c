/*!  \file     i2c.c
 *   \brief    I2C Low Level Driver for SAMD
 *   Created:  15/06/2018
 *   Author:   MBorregoTrujillo
 */
#include "i2c.h"

/*! \fn     i2c_deinit
 *  \brief  De initialize and Reset the i2c sercom
 */
void i2c_deinit(Sercom* sercom_pt){
    /* Disable SERCOM */
    sercom_pt->I2CM.CTRLA.reg = 0;
    while (sercom_pt->I2CM.SYNCBUSY.reg);
    /* Reset SERCOM */
    sercom_pt->I2CM.CTRLA.reg = SERCOM_USART_CTRLA_SWRST;
    while (sercom_pt->I2CM.SYNCBUSY.reg);
}

/*! \fn     i2c_master_init
 *  \brief  I2C master initialization
 *  \param  sercom_pt   Pointer to a sercom module
 *  \param  baud        I2C bus baudrate
 */
void i2c_master_init(Sercom* sercom_pt, uint32_t baudrate){
    sercom_pt->I2CM.CTRLA.reg = SERCOM_I2CM_CTRLA_MODE_I2C_MASTER;
    sercom_pt->I2CM.BAUD.reg = baudrate;
    sercom_pt->I2CM.CTRLA.reg = SERCOM_I2CM_CTRLA_ENABLE
                                | SERCOM_I2CM_CTRLA_MODE_I2C_MASTER;
    sercom_pt->I2CM.STATUS.reg = SERCOM_I2CM_STATUS_BUSSTATE(1);
    sercom_pt->I2CM.INTENSET.reg = SERCOM_I2CM_INTENSET_MB | SERCOM_I2CM_INTENSET_SB;
}

/*! \fn     i2c_master_write
 *  \brief  i2c master transmission from buffer
 *  \param  sercom_pt   Pointer to a sercom module
 *  \param  addr        I2C device address
 *  \param  data        buffer to transmitt
 *  \param  len         buffer length
 */
void i2c_master_write(Sercom* sercom_pt, uint8_t addr, uint8_t *data, uint8_t len){
    /* Acknowledge section is set as ACK signal by
      writing 0 in ACKACT bit */
    sercom_pt->I2CM.CTRLB.reg &= ~SERCOM_I2CM_CTRLB_ACKACT;
    while(sercom_pt->I2CM.SYNCBUSY.bit.SYSOP);
    /* Send Addr */
    sercom_pt->I2CM.INTFLAG.reg = SERCOM_I2CM_INTFLAG_MB;
    sercom_pt->I2CM.ADDR.reg = (addr << 1);
    while( (sercom_pt->I2CM.INTFLAG.reg & SERCOM_I2CM_INTFLAG_MB) == 0);
    /* Send Data */
    while(len){
        sercom_pt->I2CM.DATA.reg = *data++;
        while( (sercom_pt->I2CM.INTFLAG.reg & SERCOM_I2CM_INTFLAG_MB) == 0);
        len--;
    }
    /* Send Stop */
    sercom_pt->I2CM.CTRLB.bit.CMD = 0x3;
    while(sercom_pt->I2CM.SYNCBUSY.bit.SYSOP);
}