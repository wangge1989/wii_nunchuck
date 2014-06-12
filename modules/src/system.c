/*
 * system.c - Top level module implementation
 */
#define DEBUG_MODULE "SYS"

#include <stdbool.h>

/* FreeRtos includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

//#include "debug.h"
//#include "version.h"
//#include "config.h"
//#include "param.h"
//#include "log.h"
#include "ledseq.h"
//#include "pm.h"
#include "joystick.h"

#include "system.h"
//#include "configblock.h"
//#include "worker.h"
//#include "freeRTOSdebug.h"
//#include "uart.h"
//#include "comm.h"
//#include "stabilizer.h"
//#include "commander.h"

//#include "console.h"

/* Private variable */
static bool canFly;

static bool isInit;

/* System wide synchronisation */
xSemaphoreHandle canStartMutex;

/* Private functions */
static void systemTask(void *arg);

/* Public functions */
void systemLaunch(void)
{
  xTaskCreate(systemTask, (const char * const)"SYSTEM",
              2*configMINIMAL_STACK_SIZE, NULL, /*Piority*/2, NULL);

}

//This must be the first module to be initialized!
void systemInit(void)
{
  if(isInit)
    return;

  canStartMutex = xSemaphoreCreateMutex();
  xSemaphoreTake(canStartMutex, portMAX_DELAY);

  //configblockInit();
  //workerInit();
  //adcInit();
  ledseqInit();
  //pmInit();
  joystick_init();
    
  isInit = true;
}

bool systemTest()
{
  bool pass=isInit;
  
  //pass &= adcTest();
  pass &= ledseqTest();
  //pass &= pmTest();
  //pass &= workerTest();
  pass &= joystick_test();
  
  return pass;
}

/* Private functions implementation */

void systemTask(void *arg)
{
    bool pass = true;

    //Init the high-levels modules
    systemInit();

    pass &= systemTest();
    while(1)
    {
    }
}


/* Global system variables */
void systemStart()
{
    xSemaphoreGive(canStartMutex);
}

void systemWaitStart(void)
{
    //This permits to guarantee that the system task is initialized before other
    //tasks waits for the start event.
    while(!isInit)
        vTaskDelay(2);

    xSemaphoreTake(canStartMutex, portMAX_DELAY);
    xSemaphoreGive(canStartMutex);
}

void systemSetCanFly(bool val)
{
    canFly = val;
}

bool systemCanFly(void)
{
    return canFly;
}
