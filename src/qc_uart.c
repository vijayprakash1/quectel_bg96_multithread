/*

*@file    uart.c
*@brief   this file for setting up the all three uart port 
*
*  ---------------------------------------------------------------------------
*
*  
*  All Rights Reserved.
*  Confidential and Proprietary - Lazy Smart
*  Developed By - Vijay Prakash
*/

//////////////////////////////////////////////////////////////////////////////////
#include "qapi_uart.h"
#include "qapi_timer.h"
#include "qapi_diag.h"
#include "quectel_utils.h"
#include "quectel_uart_apis.h"
#include "qc_uart.h"



/**************************************************************************
*                                 GLOBAL
***************************************************************************/
static char *rx1_buff = NULL; /*!!! should keep this buffer as 4K Bytes */
static char *tx1_buff = NULL;
static char *rx2_buff = NULL; /*!!! should keep this buffer as 4K Bytes */
static char *tx2_buff = NULL;
static char *rx3_buff = NULL; /*!!! should keep this buffer as 4K Bytes */
static char *tx3_buff = NULL;


/* uart1 config para*/
static QT_UART_CONF_PARA uart1_conf =
{
	NULL,
	//QT_UART_PORT_04,
	QAPI_UART_PORT_001_E,
	NULL,
	0,
	NULL,
	0,
	115200  // change the baud rate as per requirement
};


/* uart2 config para*/
QT_UART_CONF_PARA uart2_conf = 
{
	NULL,
	QT_UART_PORT_02,
	NULL,
	0,
	NULL,
	0,
	115200  // change the baud rate as per requirement
};


/* uart3 config para*/
static QT_UART_CONF_PARA uart3_conf =
{
	NULL,
	QT_UART_PORT_03,
	NULL,
	0,
	NULL,
	0,
	115200   // change the baud rate as per requirement
};


/**************************************************************************
*                                 FUNCTION
***************************************************************************/

void uart1_setup(void){
	
	
		uart1_conf.tx_buff = tx1_buff;
		uart1_conf.rx_buff = rx1_buff;
		uart1_conf.tx_len = 4096;
		uart1_conf.rx_len = 4096;

		/* uart 1 init 			*/
		uart_init(&uart1_conf);       /* start uart 1 receive */
		
		uart_recv(&uart1_conf);       /* prompt task running 	*/
		
}



void _log_setup(void){      // setup function for logging using UART2
			
			uart2_conf.tx_buff = tx2_buff;
			uart2_conf.rx_buff = rx2_buff;
			uart2_conf.tx_len = 4096;
			uart2_conf.rx_len = 4096;

			/* uart 2 init 			*/
			uart_init(&uart2_conf);
			/* start uart 2 receive */
			uart_recv(&uart2_conf);
				
}




void _log(const char* fmt, ...)   // String formating for log port 
{
	va_list arg_list;
    char dbg_buffer[512] = {0};
    
	va_start(arg_list, fmt);
    vsnprintf((char *)(dbg_buffer), sizeof(dbg_buffer), (char *)fmt, arg_list);
    va_end(arg_list);
	qapi_UART_Transmit(uart2_conf.hdlr, dbg_buffer, strlen(dbg_buffer), NULL);
	qapi_UART_Transmit(uart2_conf.hdlr, "\r\n", strlen("\r\n"), NULL);
    qapi_Timer_Sleep(50, QAPI_TIMER_UNIT_MSEC, true);

	
}

int count = 0;
void uart3_cb(uint32_t num_bytes, void *cb_data)
{
  
   	count++;
    static int bytes_in_str = 0;
    QT_UART_CONF_PARA *uart3_conf = (QT_UART_CONF_PARA *)cb_data;

    // _log("numbytes=%d Counter=%d bytes_in_str=%d", num_bytes, count, bytes_in_str);
    int i = 0;
    for (i = 0; i < num_bytes; i++)
    {
        _log("%c", uart3_conf->rx_buff[i]);
    }
    //here comes the logic
    // char str[QUEUE_MESSAGE_SIZE];
    // int q_status = TX_SUCCESS;
    // int buf_index = 0;
    // while (num_bytes > 0 && num_bytes < 10)
    // {
    //     memcpy(str, (uart3_conf->rx_buff) + buf_index, 3);
    //     num_bytes -= 3;
    //     buf_index += 3;
    //     // q_status = tx_queue_send(queue_config[1].queue_handle, str, 2);
    //     if (q_status != TX_SUCCESS)
    //     {
    //         _log("CALLBACK");
    //     }
	uart_recv(&uart3_conf);

}


void setup_uart3(void){       // setup function for wifi communication using UART3
	       
		   	uart3_conf.tx_buff = tx3_buff;
			uart3_conf.rx_buff = rx3_buff;
			uart3_conf.tx_len = 4096;
			uart3_conf.rx_len = 4096;

			/* uart 3 init 			*/
			// uart_init(&uart3_conf);
           uart_init_with_cb(uart3_conf, &uart3_cb);
			/* start uart 3 receive */
			// uart_recv(&uart3_conf);
			
	
}

void uart1_print(const char* fmt, ...) 
{
	va_list arg_list;
    char dbg_buffer[512] = {0}; 
    
	va_start(arg_list, fmt);
    vsnprintf((char *)(dbg_buffer), sizeof(dbg_buffer), (char *)fmt, arg_list);
    va_end(arg_list);
	qapi_UART_Transmit(uart1_conf.hdlr, dbg_buffer, strlen(dbg_buffer), NULL);	
	//qt_uart_dbg(uart2_conf.hdlr, dbg_buffer);
}


void uart3_print(const char* fmt, ...) 
{
	va_list arg_list;
    char dbg_buffer[512] = {0};
    
	va_start(arg_list, fmt);
    vsnprintf((char *)(dbg_buffer), sizeof(dbg_buffer), (char *)fmt, arg_list);
    va_end(arg_list);
	qapi_UART_Transmit(uart3_conf.hdlr, dbg_buffer, strlen(dbg_buffer), NULL);		
	
}


