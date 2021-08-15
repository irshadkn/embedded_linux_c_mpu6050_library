//LIBRARY: EMBEDDED LINUX MPU6050 C LIBRARY
//VERSION: 1.0
//AUTHOR: MUHAMMED IRSHAD
//MAIL: irshad.kn@gmail.com

#ifndef __MPU6050_H__
#define __MPU6060_H__

#include <stdint.h>

#define WHO_AM_I_REG    0x75
#define POWR_MGNT_REG   0x6B
#define ACCL_CONF_REG   0x1C
#define GYRO_CONF_REG   0x1B
#define SMPL_DVDR_REG   0x19
#define CONFIG_REG      0x1A
#define ACCL_XH_REG     0x3B
#define ACCL_XL_REG     0x3C
#define ACCL_YH_REG     0x3D
#define ACCL_YL_REG     0x3E
#define ACCL_ZH_REG     0x3F
#define ACCL_ZL_REG     0x40
#define GYRO_XH_REG     0x43
#define GYRO_XL_REG     0x44
#define GYRO_YH_REG     0x45
#define GYRO_YL_REG     0x46
#define GYRO_ZH_REG     0x47
#define GYRO_ZL_REG     0x48
#define TEMP_HI_REG     0x41
#define TEMP_LO_REG     0x42
#define FIFO EN_REG     0x23
#define FIFO_CH_REG     0x72
#define FIFO_CL_REG     0x73
#define FIFO_REG        0x74

struct mpu6050{
	float accl_x, accl_y, accl_z, gyro_x, gyro_y, gyro_z, temperature;
};

void i2c_init(uint8_t);
void i2c_set_slave(uint8_t);
void i2c_write(uint8_t, uint8_t);
char irc_read(uint8_t);
int16_t twos_complement(uint8_t, uint8_t);
void mpu6050_init(uint8_t, uint8_t);
struct mpu6050 mpu6050_getData(); 

#endif
