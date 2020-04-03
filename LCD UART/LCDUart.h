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

#include <stdint.h>
#include <stddef.h>

unsigned char lcd_uart_tx(unsigned char *buf, unsigned char num_bytes);
unsigned char lcd_uart_write_reg(unsigned char addr, unsigned char data);

//Write Register
unsigned char lcdWriteReg(unsigned char addr, unsigned char data);

//Update the LCD
//row should be 1-4
//Data is a pointer to the data to be displayed on that particular row
//
//To clear the LCD, update each row with white space " "
inline unsigned char lcdRowWrite(unsigned char row, unsigned char *new_data);

//Special operations requiring an unlock sequence
unsigned char lcdSpecialFunction(unsigned char func);

//Updates the contrast, argument can be between 0 and 160
//Changes are not saved to non volatile memory
unsigned char lcdContrast(unsigned char val);
