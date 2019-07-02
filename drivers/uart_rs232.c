#include "uart_rs232.h"


#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "stdbool.h"
#include "stdint.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"

void uart_rs232_init(void)
{
    UART0_Config();
    UART1_Config();
    UART2_Config();
    UART3_Config();
    UART4_Config();
    UART5_Config();
    UART6_Config();
    UART7_Config();
}
void UART0_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(SeverPort, SysCtlClockGet(), SerialBaudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    IntEnable(INT_UART0);
    UARTIntEnable(SeverPort, UART_INT_RX | UART_INT_RT);
}

//******************************************************************************************************
//Function: Configurate UART1
//Input:
//Output:
//******************************************************************************************************
void UART1_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    GPIOPinConfigure(GPIO_PB0_U1RX);
  GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(SerialPort1, SysCtlClockGet(), SerialBaudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    IntEnable(INT_UART1);
    UARTIntEnable(SerialPort1, UART_INT_RX | UART_INT_RT);
}

//******************************************************************************************************
//Function: Configurate UART2
//Input:
//Output:
//******************************************************************************************************
void UART2_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
    HWREG(GPIO_PORTD_BASE + GPIO_O_AFSEL) |= 0x80;
    HWREG(GPIO_PORTD_BASE + GPIO_O_DEN) |= 0x80;
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    GPIOPinConfigure(GPIO_PD6_U2RX);
  GPIOPinConfigure(GPIO_PD7_U2TX);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    UARTConfigSetExpClk(SerialPort2, SysCtlClockGet(), SerialBaudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    IntEnable(INT_UART2);
    UARTIntEnable(SerialPort2, UART_INT_RX | UART_INT_RT);
}
//******************************************************************************************************
//Function: Configurate UART3
//Input:
//Output:
//******************************************************************************************************
void UART3_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    GPIOPinConfigure(GPIO_PC6_U3RX);
  GPIOPinConfigure(GPIO_PC7_U3TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    UARTConfigSetExpClk(SerialPort5, SysCtlClockGet(), SerialBaudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    IntEnable(INT_UART3);
    UARTIntEnable(SerialPort5, UART_INT_RX | UART_INT_RT);
}

//******************************************************************************************************
//Function: Configurate UART4
//Input:
//Output:
//******************************************************************************************************
void UART4_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
    GPIOPinConfigure(GPIO_PC4_U4RX);
  GPIOPinConfigure(GPIO_PC5_U4TX );//GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTConfigSetExpClk(SerialPort6, SysCtlClockGet(), SerialBaudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    IntEnable(INT_UART4);
    UARTIntEnable(SerialPort6, UART_INT_RX | UART_INT_RT);
}

//******************************************************************************************************
//Function: Configurate UART5
//Input:
//Output:
//******************************************************************************************************
void UART5_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
    GPIOPinConfigure(GPIO_PE4_U5RX);
  GPIOPinConfigure(GPIO_PE5_U5TX);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTConfigSetExpClk(SerialPort3, SysCtlClockGet(), SerialBaudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    IntEnable(INT_UART5);
    UARTIntEnable(SerialPort3, UART_INT_RX | UART_INT_RT);
}

//******************************************************************************************************
//Function: Configurate UART6
//Input:
//Output:
//******************************************************************************************************
void UART6_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);
    GPIOPinConfigure(GPIO_PD4_U6RX);
  GPIOPinConfigure(GPIO_PD5_U6TX);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTConfigSetExpClk(SerialPort0, SysCtlClockGet(), SerialBaudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    IntEnable(INT_UART6);
    UARTIntEnable(SerialPort0, UART_INT_RX | UART_INT_RT);
}

//******************************************************************************************************
//Function: Configurate UART7
//Input:
//Output:
//******************************************************************************************************
void UART7_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);
    GPIOPinConfigure(GPIO_PE0_U7RX);
  GPIOPinConfigure(GPIO_PE1_U7TX);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(SerialPort4, SysCtlClockGet(), SerialBaudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    IntEnable(INT_UART7);
    UARTIntEnable(SerialPort4, UART_INT_RX | UART_INT_RT);

}

