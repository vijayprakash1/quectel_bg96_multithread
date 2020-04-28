
#ifndef __QC_UART_H__
#define __QC_UART_H__





#define QT_UART_ENABLE_1ST
#define QT_UART_ENABLE_2ND
#define QT_UART_ENABLE_3RD


void uart1_setup(void);
void setup_uart3(void);
void _log_setup(void);

void _log(const char* fmt, ...);
void uart1_print(const char* fmt, ...);
void uart3_print(const char* fmt, ...);  


#endif 
