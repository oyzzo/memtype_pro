/*!  \file     oled.c
 *   \brief    OLED display driver 96x16
 *   Created:  15/06/2018
 *   Author:   MBorregoTrujillo
 */
#include "oled.h"
#include "../I2C/i2c.h"

/* Private data declaration */
static uint8_t oled_display_data[193];

/*! \fn     oled_sendcommand
 *  \brief  Sends a command byte via I2C
 *  \param  cmd     command to send to OLED display    
 */
static void oled_sendcommand(uint8_t cmd){
    //control byte //initialization byte
    uint8_t data[2] = { 0x00, cmd };
    i2c_master_write(OLED_SERCOM, OLED_I2C_ADDR, data, sizeof(data));
}
/*! \fn     oled_init
 *  \brief  Initialization of the display
 */
void oled_init(void){
    /* Reset OLED before configuring it */
    OLED_RESET();
    
    /* Init Driver */
    oled_sendcommand(0xA8); //set multiplex ratio...
    oled_sendcommand(0x0F); //...to 16-1
    oled_sendcommand(0x8D); //charge pump setting...
    oled_sendcommand(0x14); //...Enable charge pump
    oled_sendcommand(0xDA); //set COM pins hardware configuration...
    oled_sendcommand(0x02); //...to sequential COM pin configuration
    oled_sendcommand(0xAF); //set display on
    //oled_sendcommand(0xC8); //set COM output direction (remap)
    oled_sendcommand(0xA1); //set segment remap (col. 127 to SEG0)
    
    /* Init Window */
    oled_sendcommand(0x20); //set memory addressing mode ...
    oled_sendcommand(0x00); //... to horizontal addressing mode
    oled_sendcommand(0x21); //set column address
    oled_sendcommand(OLED_START_COL); //start column
    oled_sendcommand(OLED_STOP_COL); //stop column
    oled_sendcommand(0x22); //set page address
    oled_sendcommand(OLED_START_PAGE); //start page
    oled_sendcommand(OLED_STOP_PAGE); //stop page
}

/*! \fn     oled_write_display
 *  \brief  Sends data to the display 
 *  (Initialization of the window before sending data tothe display -> initWindow()
 *  \param  data    Display data to write
 *  \param  len     Data length (1 byte == 8 pixels in vertical)
 */
void oled_write_display(const uint8_t *data, uint16_t len){
    uint16_t i;
    oled_display_data[0] = 0x40; //control byte (send data)
    for(i=0;i<len;i++){
        oled_display_data[i+1] = data[i];
    }
    i2c_master_write(OLED_SERCOM, OLED_I2C_ADDR, oled_display_data, len+1);
}
