/*!  \file     main
 *   \brief    Memtype PRO main code
 *   Created:  15/06/2018
 *   Author:   MBorregoTrujillo
 */
#include "sam.h"
#include "PM/power_manager.h"
#include "CLOCK/clock_manager.h"
#include "PORT/port_manager.h"
#include "I2C/i2c.h"
#include "OLED/oled.h"

/* OLED frame */
const uint8_t oled_frame[192] = {
0,0,0,0,0,0,128,128,128,128,128,128,128,128,128,128,128,128,128,0,0,0,0,0,0,128,192,128,0,0,0,0,0,0,128,0,224,64,128,0,0,0,0,0,0,0,0,192,192,0,112,224,128,0,0,0,0,0,0,224,32,32,32,32,32,32,32,32,160,32,32,32,32,160,160,160,160,32,32,160,160,160,32,32,32,32,32,160,32,32,32,32,32,224,0,0,
0,0,0,0,0,0,15,8,10,10,10,10,10,10,10,8,8,8,15,2,0,0,4,14,15,7,3,7,15,14,4,0,0,0,8,5,63,21,8,0,0,0,0,0,2,7,2,24,29,7,112,63,15,2,0,0,0,0,0,127,64,81,74,68,64,64,80,80,95,80,80,64,64,95,84,80,80,64,64,72,84,82,81,64,64,80,80,95,80,80,64,64,64,127,0,0,
};

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();

    /* Power Manager Init */
    power_manager_init();

    /* Clock Manager Init */
    clock_manager_init();

    /* Port Init */
    port_manager_init();

    /* I2C master Init */
    i2c_master_init(OLED_SERCOM, 5);

    /* OLED Init */
    oled_init();
    
    /* Send first frame to display */
    oled_write_display(oled_frame, sizeof(oled_frame));

    /* Replace with your application code */
    while (1)
    {

    }
}


