/*!  \file     gui.c
 *   \brief    GUI library implementation
 *
 *   This file implements the GUI functions that allow to 
 *   write text and graphics to the OLED screen.
 *
 *   Created:  19/06/2018
 *   Author:   Noel Carriqui
 */
#include "../OLED/oled.h"
#include "../I2C/i2c.h"
#include "gui.h"

/* OLED test bitmap */
const uint8_t oled_test_bitmap[192] = { 0,  0,  0,  0,  0,  0,  128,    128,    128,    128,    128,
    128,    128,    128,    128, 128,    128,    128,    128,    0,  0,  0,  0,  0,  0,  128,
    192,    128,    0,  0,  0,  0, 0,  0,  128,    0,  224,    64, 128,    0,  0,  0,  0,  0,  0,
    0,  0,  192,    192,    0,  112, 224,    128,    0,  0,  0,  0,  0,  0,  224,    32, 32, 32, 32,
    32, 32, 32, 32, 160,    32, 32, 32, 32, 160,    160,    160,    160,    32, 32, 160,    160,
    160,    32, 32, 32, 32, 32, 160, 32, 32, 32, 32, 32, 224,    0,  0, 0,  0,  0,  0,  0,  0,  15,
    8,  10, 10, 10, 10, 10, 10, 10, 8,  8,  8,  15, 2,  0,  0,  4,  14, 15, 7,  3,  7,  15, 14, 4,
    0,  0,  0,  8,  5,  63, 21, 8, 0,  0,  0,  0,  0,  2,  7,  2,  24, 29, 7,  112,    63, 15, 2,
    0,  0,  0,  0,  0,  127,    64, 81, 74, 68, 64, 64, 80, 80, 95, 80, 80, 64, 64, 95, 84, 80, 80,
    64, 64, 72, 84, 82, 81, 64, 64, 80, 80, 95, 80, 80, 64, 64, 64, 127,    0,  0, };

/*! \fn     gui_init
 *  \brief  Initialization of the GUI library.
 *
 *  This function initializes the Graphical User Interface
 *  library. It has to be called before writing text or
 *  bitmaps using any GUI library function.
 */
void gui_init()
{
    /* The screen communicates by i2c */
    i2c_master_init(OLED_SERCOM,  5);

    /* OLED driver init */
    oled_init();
}

/*! \fn     gui_test
 *  \brief  Draw bitmap pattern to screen.
 *
 *  This function draws a test bitmap to the screen
 *  so a visual check can be done to assure the 
 *  oled screen is working.
 */
void gui_test()
{
    /* Render test bitmap to screen */
    oled_write_display(oled_test_bitmap,  sizeof(oled_test_bitmap));
}
