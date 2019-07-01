#ifndef UART_RS232_H_
#define UART_RS232_H_

#define SeverPort   UART0_BASE
#define SerialPort0 UART6_BASE
#define SerialPort1 UART1_BASE
#define SerialPort2 UART2_BASE
#define SerialPort3 UART5_BASE
#define SerialPort4 UART7_BASE
#define SerialPort5 UART3_BASE
#define SerialPort6 UART4_BASE



#define SerialBaudrate 115200

void UART0_Config(void);
void UART1_Config(void);
void UART2_Config(void);
void UART3_Config(void);
void UART4_Config(void);
void UART5_Config(void);
void UART6_Config(void);
void UART7_Config(void);



#endif //UART_RS232_H
