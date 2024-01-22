
#include "ILI9341.h"
#include "stm32f4xx_hal.h"

void LcdWriteReg(unsigned short Data)
{
	LCD_REG = Data;
}


void LcdWriteData(unsigned short Data)
{
	LCD_RAM = Data;
}

void LcdInit(void) {

    HAL_Delay(5);

    LcdWriteReg(ILI9341_DISPLAY_OFF);

    LcdWriteReg(ILI9341_POWERA);
    LcdWriteData(0x39);
    LcdWriteData(0x2C);
    LcdWriteData(0x00);
    LcdWriteData(0x34);
    LcdWriteData(0x02);

    LcdWriteReg(ILI9341_POWERB);
    LcdWriteData(0x00);
    LcdWriteData(0xC1);
    LcdWriteData(0x30);

    LcdWriteReg(ILI9341_DTCA);
    LcdWriteData(0x85);
    LcdWriteData(0x00);
    LcdWriteData(0x78);

    LcdWriteReg(ILI9341_DTCB);
    LcdWriteData(0x00);
    LcdWriteData(0x00);

    LcdWriteReg(ILI9341_POWER_SEQ);
    LcdWriteData(0x64);
    LcdWriteData(0x03);
    LcdWriteData(0x12);
    LcdWriteData(0x81);

    LcdWriteReg(ILI9341_PRC);
    LcdWriteData(0x20);

    LcdWriteReg(ILI9341_POWER1);
    LcdWriteData(0x23);

    LcdWriteReg(ILI9341_POWER2);
    LcdWriteData(0x10);

    LcdWriteReg(ILI9341_VCOM1);
    LcdWriteData(0x3E);
    LcdWriteData(0x28);

    LcdWriteReg(ILI9341_VCOM2);
    LcdWriteData(0x86);

    LcdWriteReg(ILI9341_MAC);
    LcdWriteData(0x48);

    LcdWriteReg(ILI9341_PIXEL_FORMAT);
    LcdWriteData(0x55);

    LcdWriteReg(ILI9341_FRC);
    LcdWriteData(0x00);
    LcdWriteData(0x18);

    LcdWriteReg(ILI9341_DFC);
    LcdWriteData(0x08);
    LcdWriteData(0x82);
    LcdWriteData(0x27);

    LcdWriteReg(ILI9341_3GAMMA_EN);
    LcdWriteData(0x00);

    LcdWriteReg(ILI9341_COLUMN_ADDR);
    LcdWriteData(0x00);
    LcdWriteData(0x00);
    LcdWriteData(0x00);
    LcdWriteData(0xEF);

    LcdWriteReg(ILI9341_PAGE_ADDR);
    LcdWriteData(0x00);
    LcdWriteData(0x00);
    LcdWriteData(0x01);
    LcdWriteData(0x3F);

    LcdWriteReg(ILI9341_GAMMA);
    LcdWriteData(0x01);

    LcdWriteReg(ILI9341_PGAMMA);
    LcdWriteData(0x0F);
    LcdWriteData(0x31);
    LcdWriteData(0x2B);
    LcdWriteData(0x0C);
    LcdWriteData(0x0E);
    LcdWriteData(0x08);
    LcdWriteData(0x4E);
    LcdWriteData(0xF1);
    LcdWriteData(0x37);
    LcdWriteData(0x07);
    LcdWriteData(0x10);
    LcdWriteData(0x03);
    LcdWriteData(0x0E);
    LcdWriteData(0x09);
    LcdWriteData(0x00);

    LcdWriteReg(ILI9341_NGAMMA);
    LcdWriteData(0x00);
    LcdWriteData(0x0E);
    LcdWriteData(0x14);
    LcdWriteData(0x03);
    LcdWriteData(0x11);
    LcdWriteData(0x07);
    LcdWriteData(0x31);
    LcdWriteData(0xC1);
    LcdWriteData(0x48);
    LcdWriteData(0x08);
    LcdWriteData(0x0F);
    LcdWriteData(0x0C);
    LcdWriteData(0x31);
    LcdWriteData(0x36);
    LcdWriteData(0x0F);

    LcdWriteReg(ILI9341_SLEEP_OUT);
    HAL_Delay(100);

	LcdWriteReg(ILI9341_MAC);
	LcdWriteData(0x28);

    LcdWriteReg(ILI9341_DISPLAY_ON);
    LcdWriteReg(ILI9341_GRAM);

}

void Set_Address(short X1,short Y1,short X2,short Y2)
{
	LcdWriteReg(ILI9341_COLUMN_ADDR);
	LcdWriteData(X1>>8);
	LcdWriteData(X1);
	LcdWriteData(X2>>8);
	LcdWriteData(X2);

	LcdWriteReg(ILI9341_PAGE_ADDR);
	LcdWriteData(Y1>>8);
	LcdWriteData(Y1);
	LcdWriteData(Y2>>8);
	LcdWriteData(Y2);

	LcdWriteReg(ILI9341_GRAM);
}
