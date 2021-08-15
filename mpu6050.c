//LIBRARY: EMBEDDED LINUX MPU6050 C LIBRARY
//VERSION: 1.0
//AUTHOR: MUHAMMED IRSHAD
//MAIL: irshad.kn@gmail.com

#include "mpu6050.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <i2c/smbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

int file;

void i2c_init(uint8_t i2c_number)
{
	char filename[20];
	snprintf(filename, 19, "/dev/i2c-%d", i2c_number);
	file = open(filename, O_RDWR);
	if (file < 0) {
  		printf("I2C %hhu Not Found\n", i2c_number);
  		exit(1);
	}
}

void i2c_set_slave(uint8_t slave_addr)
{
	if (ioctl(file, I2C_SLAVE, slave_addr) < 0) {
  		printf("I2C Slave Not Found");
		exit(1);
	}
}

void i2c_write(uint8_t reg_addr, uint8_t reg_value)
{
	char buf[2];
	buf[0] = reg_addr;
	buf[1] = reg_value;
	if (write(file, buf, 2) != 2) {
  		printf("I2C Write Operation Failed\n");
	}
}

char i2c_read(uint8_t reg_addr)
{
	char buf[1];
	buf[0] = reg_addr;
	if (write(file, buf, 1) != 1) {
  		printf("Invalid Register");
	}
	if (read(file, buf, 1) != 1) {
  		printf("I2C Read Operation Failed");
	} 
	else {
  		return buf[0];
	}
}

int16_t twos_complement(uint8_t higher_byte, uint8_t lower_byte)
{
	uint16_t word = (uint16_t)((higher_byte << 8) | lower_byte);
	int16_t signed_word;
	if((word & 0x8000) != 0)
	{
		word = ~word + 0x0001;
		signed_word = (int16_t)(word * -1);
		return signed_word;
	}
	else 
	{
		signed_word = (int16_t)word;
		return signed_word;
	}
}

void mpu6050_init(uint8_t i2c_number, uint8_t slave_addr)
{
	i2c_init(i2c_number);
	i2c_set_slave(slave_addr);
	i2c_write(POWR_MGNT_REG, 0x01);
	i2c_write(ACCL_CONF_REG, 0x00);
	i2c_write(GYRO_CONF_REG, 0x00);
}

struct mpu6050 mpu6050_getData() 
{
	struct mpu6050 obj;
	char axh, axl, ayh, ayl, azh, azl, gxh, gxl, gyh, gyl, gzh, gzl, th, tl;
        int16_t axw, ayw, azw, gxw, gyw, gzw, tw;

 	axh = i2c_read(ACCL_XH_REG);
        axl = i2c_read(ACCL_XL_REG);
        ayh = i2c_read(ACCL_YH_REG);
        ayl = i2c_read(ACCL_YL_REG);
        azh = i2c_read(ACCL_ZH_REG);
        azl = i2c_read(ACCL_ZL_REG);
	gxh = i2c_read(GYRO_XH_REG);
        gxl = i2c_read(GYRO_XL_REG);
        gyh = i2c_read(GYRO_YH_REG);
        gyl = i2c_read(GYRO_YL_REG);
        gzh = i2c_read(GYRO_ZH_REG);
        gzl = i2c_read(GYRO_ZL_REG);
	th = i2c_read(TEMP_HI_REG);
        tl = i2c_read(TEMP_LO_REG);

        axw = twos_complement(axh, axl);
        ayw = twos_complement(ayh, ayl);
        azw = twos_complement(azh, azl);
	gxw = twos_complement(gxh, gxl);
        gyw = twos_complement(gyh, gyl);
        gzw = twos_complement(gzh, gzl);
	tw = twos_complement(th, tl);

        obj.accl_x = ((float)axw)/16384;
        obj.accl_y = ((float)ayw)/16384;
        obj.accl_z = ((float)azw)/16384;
	obj.gyro_x = ((float)gxw)/131.072;
        obj.gyro_y = ((float)gyw)/131.072;
        obj.gyro_z = ((float)gzw)/131.072;
	obj.temperature = 36.53 + (((float)tw)/340);
	return obj;
}
