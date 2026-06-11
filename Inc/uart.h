/*
 * uart.h
 *
 *  Created on: Jun 10, 2026
 *      Author: kevindzouza
 */

#ifndef INC_UART_H_
#define INC_UART_H_

void MX_USART1_UART_Init(void);
int __io_putchar(int ch);
int Uart_write(int ch);



#endif /* INC_UART_H_ */
