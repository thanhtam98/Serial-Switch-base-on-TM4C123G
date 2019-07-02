#include "data_handler.h"
#include "drivers/uart_rs232.h"
#include "app/circular_buffer/circular_buffer.h"
#include "app/afproto/afproto.h"

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

unsigned int write_len;

#define MAX_BUFFER_SIZE 1024

 uint8_t rawBuffer[7][MAX_BUFFER_SIZE];
 circBuf_t rawCircBuffer[7];

void circ_buffer_init(void)
{

    int Port;
    for ( Port = Port0 ; Port < Port7 ; ++Port)
    {
        rawCircBuffer[Port]= (circBuf_t){
                          .buffer = rawBuffer[Port],
                          .head   = 0,
                          .tail    = 0,
                          .maxLen  = MAX_BUFFER_SIZE
        };
    }
}

void circ_buffer_process(void)
{
    int Port;
    for (Port = Port0 ; Port < Port7; ++Port)
    {
        char rawFrame[100];
        char payLoad[100];
        char repFrame[100];
        int count = 0;
        uint8_t readByte ;
        bool IsSending = 0;
        bool IsPackage = 0;
        while( circBufPop(&rawCircBuffer[Port], &readByte) != -1)   // loop until buffer is empty
        {
            if(readByte == AFPROTO_START_BYTE)
            {
                rawFrame[count] = readByte;
                count = 1;
                IsPackage = 1;
            }
            if (IsPackage == 1)
            {
                if(readByte == AFPROTO_END_BYTE)
                {
                    rawFrame[count] = readByte;
                    count ++;
                    IsPackage = 0;
                    IsSending = 1;
                }
                else
                {
                    rawFrame[count] = readByte;
                    count++;
                }

            }
            if(IsSending == 1)
            {
                uint8_t size;
                uint8_t length;
                int8_t temp = 0;
                for (size = 0; size < count; size++)
                {
                    temp = afproto_get_data(rawFrame, size, payLoad, &write_len);
                }
                if(temp > 0)
                {
                    length = write_len;
                    payLoad[1] = Port;
                    uint8_t i;
                    for (i = 0; i < length; i++)
                    {
                        afproto_frame_data(payLoad, length, repFrame, &write_len);
                    }
                    length = write_len +1;
                    for (i = 0; i < length; i++)
                    {
                        UARTCharPut(SeverPort, repFrame[i]);
                    }

                }
                IsSending = 0;
                count = 0;
            }
        }

    }
}


void SeverIntHandler(void) //Uart0
{

    unsigned long ulStatus;
    ulStatus = UARTIntStatus(SeverPort, true); //get interrupt status
    UARTIntClear(SeverPort, ulStatus); //clear the asserted interrupts

}

//******************************************************************************************************
//Function: UART0 Handler
//Input:
//Output:
//******************************************************************************************************
void Port0IntHandler(void) //UART6
{
    unsigned long ulStatus;
    ulStatus = UARTIntStatus(SerialPort0, true); //get interrupt status
    UARTIntClear(SerialPort0, ulStatus); //clear the asserted interrupts

    circBufPush(&rawCircBuffer[Port0],UARTCharGet(SerialPort0));
}

//******************************************************************************************************
//Function: UART0 Handler
//Input:
//Output:
//******************************************************************************************************
void Port1IntHandler(void) //UART1
{
    unsigned long ulStatus;
    ulStatus = UARTIntStatus(SerialPort1, true); //get interrupt status
    UARTIntClear(SerialPort1, ulStatus); //clear the asserted interrupts

    circBufPush(&rawCircBuffer[Port1],UARTCharGet(SerialPort1));
}

//******************************************************************************************************
//Function: UART0 Handler
//Input:
//Output:
//******************************************************************************************************
void Port2IntHandler(void) //UART2
{
    unsigned long ulStatus;
    ulStatus = UARTIntStatus(SerialPort2, true); //get interrupt status
    UARTIntClear(SerialPort2, ulStatus); //clear the asserted interrupts

    circBufPush(&rawCircBuffer[Port2],UARTCharGet(SerialPort2));
}

//******************************************************************************************************
//Function: UART0 Handler
//Input:
//Output:
//******************************************************************************************************
void Port3IntHandler(void) //UART5
{
    unsigned long ulStatus;
    ulStatus = UARTIntStatus(SerialPort3, true); //get interrupt status
    UARTIntClear(SerialPort3, ulStatus); //clear the asserted interrupts

    circBufPush(&rawCircBuffer[Port3],UARTCharGet(SerialPort3));
}

//******************************************************************************************************
//Function: UART0 Handler
//Input:
//Output:
//******************************************************************************************************
void Port4IntHandler(void) //UART7
{
    unsigned long ulStatus;
    ulStatus = UARTIntStatus(SerialPort4, true); //get interrupt status
    UARTIntClear(SerialPort4, ulStatus); //clear the asserted interrupts

    circBufPush(&rawCircBuffer[Port4],UARTCharGet(SerialPort4));
}

//******************************************************************************************************
//Function: UART0 Handler
//Input:
//Output:
//******************************************************************************************************
void Port5IntHandler(void) //UART3
{
    unsigned long ulStatus;
    ulStatus = UARTIntStatus(SerialPort5, true); //get interrupt status
    UARTIntClear(SerialPort5, ulStatus); //clear the asserted interrupts

    circBufPush(&rawCircBuffer[Port5],UARTCharGet(SerialPort5));
}

//******************************************************************************************************
//Function: UART0 Handler
//Input:
//Output:
//******************************************************************************************************
void Port6IntHandler(void) //UART4
{
    unsigned long ulStatus;
    ulStatus = UARTIntStatus(SerialPort6, true); //get interrupt status
    UARTIntClear(SerialPort6, ulStatus); //clear the asserted interrupts

    circBufPush(&rawCircBuffer[Port6],UARTCharGet(SerialPort6));
}
