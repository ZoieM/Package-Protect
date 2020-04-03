#include "string.h"
#include "stdio.h"
#include "LCDUart.h"

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Driver configuration */
#include "ti_drivers_config.h"

unsigned char lcd_uart_tx(unsigned char *buf, unsigned char num_bytes)
{
    unsigned char x;

    for(x = 0; x < num_bytes; x++)
    {
        UART_write(uart, &buf[x], 1);
        vTaskDelay(1);
    }

    return 0;
}
unsigned char lcd_uart_write_reg(unsigned char addr, unsigned char data)
{
    unsigned char buf[2];

    //Send read request
    buf[0] = CONST_LCD_UART_REG_WRITE | addr;
    buf[1] = data;

    lcd_uart_tx(buf, 2);
    vTaskDelay(1);

    return 0;
}

//Write Register
unsigned char lcdWriteReg(unsigned char addr, unsigned char data)
{
    lcd_uart_write_reg(addr, data);
    return 0;
}

//Update the LCD
//row should be 1-4
//Data is a pointer to the data to be displayed on that particular row
//
//To clear the LCD, update each row with white space " "
inline unsigned char lcdRowWrite(unsigned char row, unsigned char *new_data)
{
    unsigned char y;
    unsigned char data_string[CONST_LCD_WIDTH+1];

    //Check row number
    if((row < 1) || (row > CONST_LCD_NUM_ROWS))
    {   return 1;
    }

//    //Check length of string
    y = strlen((char*)new_data);
    if(y > CONST_LCD_WIDTH)
    {   return 1;
    }

    //Initialize to empty
    memset(data_string, CONST_LCD_EMPTY, sizeof(data_string));

    //copy the new data
    memcpy(data_string, new_data, y);

    //Write to LCD
    for(y = 0; y < CONST_LCD_WIDTH; y++)
    { lcdWriteReg(CONST_ADDR_LCD_DATA_START + y, data_string[y]);
    }

    //Issue update command
    lcdWriteReg(CONST_ADDR_LCD_ACTION, (row-1) | CONST_LCD_ACTION_GO_BIT);

   //Wait for LCD update
    vTaskDelay(5);

    return 0;
}
//Special operations requiring an unlock sequence
unsigned char lcdSpecialFunction(unsigned char func)
{
    unsigned char x;

    x = lcdWriteReg(CONST_ADDR_SPCL_REG, func);
    x |= lcdWriteReg(CONST_ADDR_UNLOCK1_REG, CONST_UNLOCK1);
    x |= lcdWriteReg(CONST_ADDR_UNLOCK2_REG, CONST_UNLOCK2);

    //Wait a little bit
    vTaskDelay(5);
    return x;
}
//Updates the contrast, argument can be between 0 and 160
//Changes are not saved to non volatile memory
unsigned char lcdContrast(unsigned char val)
{   unsigned char y;

    y = lcdWriteReg(CONST_ADDR_SPCL_W_REG_1, val);
    y |= lcdSpecialFunction(CONST_SPL_FUNC_LCD_CONTRAST);
    return y;
}
