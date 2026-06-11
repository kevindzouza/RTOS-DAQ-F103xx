/*
 * I2C.h
 *
 *  Created on: Jun 9, 2026
 *      Author: kevindzouza
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

extern volatile int16_t accelX;
extern volatile int16_t accelY;
extern volatile int16_t accelZ;

extern volatile int16_t gyroX;
extern volatile int16_t gyroY;
extern volatile int16_t gyroZ;

extern volatile int16_t tempRaw;

void MX_I2C1_Init(void);
void wakeUpMpu(void);
void collectData(void);


#endif /* INC_I2C_H_ */
