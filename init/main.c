/**
 * main.c - Containing the main function.
 */

/* FreeRtos includes */
#include "FreeRTOS.h"
#include "task.h"

/* ST includes */
#include "stm32f30x.h"

/* Personal configs */
#include "FreeRTOSConfig.h"

/* Project includes */
#include "system.h"

int main(void)
{

    //Launch the system task that will initialize and start everything
    systemLaunch();

    //Start the FreeRTOS scheduler
    vTaskStartScheduler();
  
    //Should never reach this point!
    while(1);

    return 0;
}
