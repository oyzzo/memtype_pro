/*!  \file     main
 *   \brief    Memtype PRO main code
 *   Created:  15/06/2018
 *   Author:   MBorregoTrujillo
 */
#include "sam.h"
#include "PM/power_manager.h"
#include "CLOCK/clock_manager.h"
#include "PORT/port_manager.h"
#include "GUI/gui.h"


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

    /* GUI Init */
    gui_init();

    /* Draw GUI test pattern */
    gui_test();
    
    /* Replace with your application code */
    while (1)
    {

    }
}


