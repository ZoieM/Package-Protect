/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== uartecho.c ========
 */




//derek added from here
#define CONST_LCD_NUM_ROWS 4
#define CONST_LCD_WIDTH 20
#define CONST_MAX_LCD_CONTRAST 160
#define CONST_MAX_LCD_BACKLIGHT 160

/////////////////////////////////////////////////
//Communication modes
/////////////////////////////////////////////////
#define CONST_MODE_I2C              0
#define CONST_MODE_UART_9600        1
#define CONST_MODE_UART_19200       2
#define CONST_MODE_UART_38400       3
#define CONST_MODE_UART_57600       4
#define CONST_MODE_UART_115200      5
#define CONST_MODE_SPI_CPOL0_CPHA0    6
#define CONST_MODE_SPI_CPOL0_CPHA1    7
#define CONST_MODE_SPI_CPOL1_CPHA0    8
#define CONST_MODE_SPI_CPOL1_CPHA1    9

/////////////////////////////////////////////////
//Unlock commands
/////////////////////////////////////////////////
#define CONST_SPL_FUNC_CPU_RESET                0
#define CONST_SPL_FUNC_LCD_CONTRAST                 3
#define CONST_SPL_FUNC_LCD_CONTRAST_SAVE        4
#define CONST_SPL_FUNC_LCD_BACKLIGHT                5
#define CONST_SPL_FUNC_LCD_BACKLIGHT_SAVE       6
#define CONST_SPL_FUNC_I2C                      13
#define CONST_SPL_FUNC_INTERFACE                14

/////////////////////////////////////////////////
//Registers
/////////////////////////////////////////////////
#define CONST_LCD_DATA_SIZE             21
#define CONST_LCD_ACTION_GO_BIT             (1 << 7)
#define CONST_ERR_FLASH_BIT            (1 << 0)
#define CONST_LCD_EMPTY 0x20
#define CONST_UNLOCK1 0x12
#define CONST_UNLOCK2 0x34
#define CONST_ADDR_ID_REG_DEF           0x3F

#define CONST_ADDR_ID_REV               0
#define CONST_ADDR_BTL_REV              1
#define CONST_ADDR_PCB_REV              2
#define CONST_ADDR_PCBA_REV             3
#define CONST_ADDR_FW_REV               4
#define CONST_ADDR_I2C_DEV_ADDR         5
#define CONST_ADDR_LCD_CONTRAST         6
#define CONST_ADDR_LCD_BACKLIGHT        7
#define CONST_ADDR_LCD_NUM_ROWS         8
#define CONST_ADDR_LCD_CHARS_PER_ROW    9
#define CONST_ADDR_LCD_R0_ADDR          10
#define CONST_ADDR_LCD_R1_ADDR          11
#define CONST_ADDR_LCD_R2_ADDR          12
#define CONST_ADDR_LCD_R3_ADDR          13
#define CONST_ADDR_INTR_ADDR            14
#define CONST_ADDR_ERR_REG              15

//Above here are read only registers
#define CONST_ADDR_I2C_READ_REG         16
#define CONST_ADDR_SPCL_W_REG_1         17
#define CONST_ADDR_SPCL_REG             18
#define CONST_ADDR_UNLOCK1_REG          19
#define CONST_ADDR_UNLOCK2_REG          20

#define CONST_ADDR_LCD_ACTION           21
#define CONST_ADDR_LCD_DATA_START       22
#define CONST_ADDR_LCD_DATA_END         (CONST_ADDR_LCD_DATA_START + CONST_LCD_DATA_SIZE)

#define CONST_LAST_REG_ADDR     CONST_ADDR_LCD_DATA_END
#define CONST_FIRST_WRITE_REG_ADDR  CONST_ADDR_I2C_READ_REG

//Wait 100uS
#define LCD_UART_RX_DELAY {sys_delay_ms(1);}

//Wait 100uS
#define LCD_UART_TX_DELAY {sys_delay_ms(1);}

//Wait 200uS
#define LCD_SPI_TX_DELAY  {sys_delay_ms(1);}

#define CONST_LCD_UART_REG_READ (0x00)
#define CONST_LCD_UART_REG_WRITE (0x80)
//derek added to here





#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdio.h"

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Driver configuration */
#include "ti_drivers_config.h"

UART_Handle uart;
UART_Params uartParams;





//derek added from here
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
//derek added to here




/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    char        input;
//    UART_Handle uart;
//    UART_Params uartParams;

    /* Call driver init functions */
    GPIO_init();
    UART_init();

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;

    uart = UART_open(0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }

    /* Loop forever echoing */
    while (1) {
//        input = 'a';
//        UART_write(uart, &input, 1);
//        input = 'b';
//        UART_write(uart, &input, 1);


        unsigned char x = 0, y;
        unsigned char buf[CONST_LAST_REG_ADDR+1];

        //Test Contrast
        for(y = 0; y <= CONST_MAX_LCD_CONTRAST; y+=10)
        {   x |= lcdContrast(y);

            sprintf((char*)buf, "Contrast = %d/%d", y,CONST_MAX_LCD_CONTRAST);
            x |= lcdRowWrite(4,buf);
            //add a delay here for readability
        }

//        lcdSpecialFunction(CONST_SPL_FUNC_CPU_RESET);//Hard Reset the LCD
        //Example that writes to each row
        //Erase
        for(y = 0; y <= CONST_LCD_NUM_ROWS; y++)
        {   sprintf((char*) buf, " ");
            x |= lcdRowWrite(y,buf);
        }
        vTaskDelay(1000);
        //Write
        for(y = 0; y <= CONST_LCD_NUM_ROWS; y++)
        {
            sprintf((char*)buf, "Row %d",y);
            x |= lcdRowWrite(y,buf);
        }
    }
}
