

#include "OV7670.h"
#include "stm32f4xx_hal.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

const uint8_t OV7670_reg[][2] = {
 {REG_COM7, 0x80},
 {REG_CLKRC, 0x80}, 
 {REG_COM11, 0x0A},
 {REG_TSLB, 0x04},
 {REG_TSLB, 0x04},
 {REG_COM7, 0x04}, 

 {REG_RGB444, 0x00}, 
 {REG_COM15, 0xD0}, 

 {REG_HSTART, 0x16},
 {REG_HSTOP, 0x04},
 {REG_HREF, 0x24},
 {REG_VSTART, 0x02},
 {REG_VSTOP, 0x7a},
 {REG_VREF, 0x0a},
 {REG_COM10, 0x02},
 {REG_COM3, 0x04},
 {REG_MVFP, 0x3f},


#if RES_320x240
 // 320x240
 {REG_COM14, 0x19},
 {0x72, 0x11},
 {0x73, 0xf1},
#else
 // 160x120
 {REG_COM14, 0x1a},
 {0x72, 0x22},
 {0x73, 0xf2},
#endif

 {0x4f, 0x80},
 {0x50, 0x80},
 {0x51, 0x00},
 {0x52, 0x22},
 {0x53, 0x5e},
 {0x54, 0x80},
 {0x56, 0x40},
 {0x58, 0x9e},
 {0x59, 0x88},
 {0x5a, 0x88},
 {0x5b, 0x44},
 {0x5c, 0x67},
 {0x5d, 0x49},
 {0x5e, 0x0e},
 {0x69, 0x00},
 {0x6a, 0x40},
 {0x6b, 0x0a},
 {0x6c, 0x0a},
 {0x6d, 0x55},
 {0x6e, 0x11},
 {0x6f, 0x9f},

 {0xb0, 0x84},

 {0xFF, 0xFF},

};

char ov7670_init(void)
{
	  ov7670_write(0x12, 0x80);
	  HAL_Delay(30);

	  uint8_t buffer[4];
	  ov7670_read(REG_VER, buffer);
	  if ( buffer[0] != 0x73)
	  {
		  return 0;
	  }
	  else
	  {
		  ov7670_config();
	  }

	  return 1;
}

char ov7670_config()
{
	ov7670_write(0x12, 0x80);
    HAL_Delay(30);

  for(int i = 0; OV7670_reg[i][0]!=0xFF; i++) {
    ov7670_write(OV7670_reg[i][0], OV7670_reg[i][1]);
    HAL_Delay(1);
  }
  return 0;
}

char ov7670_write(uint8_t regAddr, uint8_t data)
{
  HAL_StatusTypeDef ret;
  do {
    ret = HAL_I2C_Mem_Write(&hi2c1, 0x42, regAddr, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
  } while (ret != HAL_OK && 0);
  return 0;
}

char ov7670_read(uint8_t regAddr, uint8_t *data)
{
  HAL_StatusTypeDef ret;
  do {
    ret = HAL_I2C_Master_Transmit(&hi2c1, 0x42, &regAddr, 1, 100);
    ret |= HAL_I2C_Master_Receive(&hi2c1, 0x42, data, 1, 100);
  } while (ret != HAL_OK && 0);
  return ret;
}
