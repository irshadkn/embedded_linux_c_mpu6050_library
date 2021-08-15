#include <stdio.h>
#include "mpu6050.h"

int main()
{
	mpu6050_init(1, 0x68); //1 - I2C Port Number; 0x68 - Slave(MPU6050)Address
	struct mpu6050 data = mpu6050_getData();
	printf("ACCL X: %.2f g \t",data.accl_x);
	printf("ACCL Y: %.2f g \t",data.accl_y);
	printf("ACCL Z: %.2f g \n",data.accl_z);
	printf("GYRO X: %.2f °/S \t",data.gyro_x);
	printf("GYRO Y: %.2f °/S \t",data.gyro_y);
	printf("GYRO Z: %.2f °/S \n",data.gyro_z);
	printf("TEMPERATURE: %.2f °C \n",data.temperature);
}
