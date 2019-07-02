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

#define MAX_BUFFER_SIZE 1024
#define TX_BUF_SIZE 100
#define MAX_ERROR_LEN 50

unsigned int write_len;
int len;
int i,j;
int temp;
int size;
char BufferReply[8][2*TX_BUF_SIZE];
char PayLoad[8][TX_BUF_SIZE];

// uint8_t rawBufferServer[8*MAX_BUFFER_SIZE];
 uint8_t rawBuffer[8][MAX_BUFFER_SIZE];
 circBuf_t rawCircBuffer[8];



 bool IsSending[8];

 bool BufferFlag[8];

 volatile int Count[8];

 volatile int BufferLength[8];

 volatile uint8_t ReadByte[8];

 char RawBuffer[8][TX_BUF_SIZE];



void circ_buffer_init(void)
{

    int Port;
    for ( Port = Port0 ; Port < PortServer + 1  ; Port++)
    {
        rawCircBuffer[Port]= (circBuf_t){
                          .buffer = rawBuffer[Port] ,
                          .head   = 0,
                          .tail    = 0,
                          .maxLen  = MAX_BUFFER_SIZE
        };
    }
//    rawCircBuffer[PortServer]= (circBuf_t){
//                              .buffer = rawBuffer[PortServer],
//                              .head   = 0,
//                              .tail    = 0,
//                              .maxLen  = MAX_BUFFER_SIZE
//            };

}
void ClearRXBuffer(uint8_t port_t)
{
    int i;
    for (i=0; i<TX_BUF_SIZE; i++)
    {
        RawBuffer[port_t][i]=0;
    }
}
void circ_buffer_get(uint8_t port_t)
{
            uint8_t readByte;
            while( (circBufPop(&rawCircBuffer[port_t], &readByte) != -1) )  // loop until buffer is empty
            {
                if(Count[port_t] > MAX_ERROR_LEN)
                    {
                        Count[port_t] = 0;
//                        break;
                    }
                ReadByte[port_t] = readByte;
                if(IsSending[port_t]== true )
                        {
                            if(ReadByte[port_t]==AFPROTO_END_BYTE)
                            {
                                RawBuffer[port_t][Count[port_t]]=ReadByte[port_t];
                                Count[port_t]++;
                                BufferLength[port_t] = Count[port_t];
                                Count[port_t] = 0;
                                IsSending[port_t] = false;
                                BufferFlag[port_t] = true;
                                break;                         //when captured a frame, break loop to process this frame
                            }
                            else
                            {
                                RawBuffer[port_t][Count[port_t]]=ReadByte[port_t];
                                Count[port_t]++;
                            }
                        }
                else
                        {
                            if(ReadByte[port_t]==AFPROTO_START_BYTE)
                            {
                                Count[port_t] = 0;
                                IsSending[port_t] = true;
                                RawBuffer[port_t][Count[port_t]] = ReadByte[port_t];
                                Count[port_t]++;
                            }
                        }
            }
}
void circ_buffer_transmit(uint8_t port_t)
{
    if(BufferFlag[port_t] == true)
    {
        for (size =0; size < BufferLength[port_t]; size++)
        {
            temp = afproto_get_data(RawBuffer[port_t], size, PayLoad[port_t], &write_len);
        }
        if (temp>0)
        {
            if(port_t == PortServer)
            {
                len = write_len;
                for (i = 0; i < len; i++)
                {
                    afproto_frame_data(PayLoad[port_t], len, BufferReply[port_t], &write_len);
                }
                len = write_len+1;
                for (j = 0; j <len ; j++)
                {
                    switch (PayLoad[port_t][1]){
                    case Port0 :
                        UARTCharPut(SerialPort0,BufferReply[port_t][j]);
                        break;
                    case Port1 :
                        UARTCharPut(SerialPort1,BufferReply[port_t][j]);
                        break;
                    case Port2 :
                        UARTCharPut(SerialPort2,BufferReply[port_t][j]);
                        break;
                    case Port3 :
                        UARTCharPut(SerialPort3,BufferReply[port_t][j]);
                        break;
                    case Port4 :
                        UARTCharPut(SerialPort4,BufferReply[port_t][j]);
                        break;
                    case Port5 :
                        UARTCharPut(SerialPort5,BufferReply[port_t][j]);
                        break;
                    case Port6 :
                        UARTCharPut(SerialPort6,BufferReply[port_t][j]);
                        break;
                    }
                }
            }
            else
            {
                len = write_len;
                PayLoad[port_t][1] = port_t;
                for (i = 0; i < len; i++)
                {
                    afproto_frame_data(PayLoad[port_t], len, BufferReply[port_t], &write_len);
                }
                len = write_len+1;
                for (j = 0; j <len ; j++)
                {
                UARTCharPut(SeverPort,BufferReply[port_t][j]);
                }
            }
        }
        ClearRXBuffer(port_t);
        BufferFlag[port_t] = false;
    }



}
void circ_buffer_process(void)
{
    uint8_t Port;

    for (Port = Port0 ; Port < PortServer + 1 ; Port++)
    {
        circ_buffer_get(Port);
        circ_buffer_transmit(Port);
    }

}


void SeverIntHandler(void) //Uart0
{

    unsigned long ulStatus;
    ulStatus = UARTIntStatus(SeverPort, true); //get interrupt status
    UARTIntClear(SeverPort, ulStatus); //clear the asserted interrupts
    circBufPush(&rawCircBuffer[PortServer], UARTCharGet(SeverPort));
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
