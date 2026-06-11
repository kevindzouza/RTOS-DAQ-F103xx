
#include "stm32f1xx_hal.h"
#include <math.h>

#define MPU_ADDR   (0x68 << 1)
#define PWR_MGMT_1 0x6B
#define VAL_ADDR   0x3B

volatile uint8_t data[14];
volatile int16_t accelX,accelY,accelZ,tempRaw,gyroX,gyroY,gyroZ,temp;
float temperature,ax,ay,az,mag;
volatile float gyroX_dps;
volatile float gyroY_dps;
volatile float gyroZ_dps;



 I2C_HandleTypeDef hi2c1;

 void wakeUpMpu(void)
 {
	 uint8_t wake = 0x00;
	 HAL_I2C_Mem_Write(&hi2c1, MPU_ADDR, PWR_MGMT_1,I2C_MEMADD_SIZE_8BIT, &wake, 1, 100);
 }

 void collectData(void)
 {
	 HAL_I2C_Mem_Read(&hi2c1, MPU_ADDR, VAL_ADDR, I2C_MEMADD_SIZE_8BIT, (uint8_t *)data, 14, 100);

	  accelX = (data[0] << 8) | data[1];
	  accelY = (data[2] << 8) | data[3];
	  accelZ = (data[4] << 8) | data[5];

	  ax = accelX / 16384.0f;
	  ay = accelY / 16384.0f;
	  az = accelZ / 16384.0f;

	  mag = sqrtf(ax*ax + ay*ay + az*az);

	  tempRaw = (data[6] << 8) | data[7];

	  gyroX  = (data[8]  << 8) | data[9];
	  gyroY  = (data[10] << 8) | data[11];
	  gyroZ  = (data[12] << 8) | data[13];


	  gyroX_dps = gyroX / 131.0f;
	  gyroY_dps = gyroY / 131.0f;
	  gyroZ_dps = gyroZ / 131.0f;

	  temperature = (tempRaw / 340.0f) + 36.53f;

 }

 void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

