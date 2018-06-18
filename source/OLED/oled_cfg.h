/*!  \file     oled_cfg.h
 *   \brief    OLED display driver 96x16 configuration file
 *   Created:  15/06/2018
 *   Author:   MBorregoTrujillo
 */
#ifndef OLED_CFG_H_
#define OLED_CFG_H_

/*!
 * \def OLED_SERCOM
 * Configures OLED SERCOM
 * example: ((Sercom*)SERCOM0)
 */
#define OLED_SERCOM     ((Sercom*)SERCOM0)

/*!
 * \def OLED_I2C_ADDR
 * Configures OLED I2C address
 * \note address range from 0 to 0x7F
 */
#define OLED_I2C_ADDR     (0x3C)

/*!
 * \def OLED_RESET
 * Performs a reset of the OLED display
 */
#define OLED_RESET()   do {\
                            REG_PORT_OUTCLR0 = (1 << 6);\
                            {volatile uint32_t i = 100; while(i--);}\
                            REG_PORT_OUTSET0 = (1 << 6);\
                            {volatile uint32_t i = 100; while(i--);}\
                       }while(0);
                       
/*!
 * \def OLED_START_COL
 * \def OLED_STOP_COL
 * \def OLED_START_PAGE
 * \def OLED_STOP_PAGE
 * Oled window configuration for 96x16 pixels
 */
#define OLED_START_COL      (0u)
#define OLED_STOP_COL       (95u)
#define OLED_START_PAGE     (0u)
#define OLED_STOP_PAGE      (1u)

#endif /* OLED_CFG_H_ */
