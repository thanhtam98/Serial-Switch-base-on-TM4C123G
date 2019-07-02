#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

#include "app/data_handler/data_handler.h"
#include "drivers/uart_rs232.h"
void main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_12MHZ);
    uart_rs232_init();
    circ_buffer_init();

    while(true)
    {
        circ_buffer_process();

        SysCtlDelay(SysCtlClockGet()/300);
    }



}
