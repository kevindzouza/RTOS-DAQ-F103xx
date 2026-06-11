#include "stm32f1xx_hal.h"

UART_HandleTypeDef huart1;

void MX_USART1_UART_Init(void);

int __io_putchar(int ch)
{
   //HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
    Uart_write(ch);
	return ch;
}

int Uart_write(int ch)
{
	while(!( USART1 -> SR & (1U<<7)))
	{
	}
	USART1 -> DR = ch;
}


void MX_USART1_UART_Init(void)
{


  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
  }

}
