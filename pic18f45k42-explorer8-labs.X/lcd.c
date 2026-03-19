/**
  EasyPIC v7 LCD Source File

  @Company
    Microchip Technology Inc.

  @File Name
    lcd.c

  @Summary
    HD44780 4-bit parallel LCD driver for EasyPIC v7.

  @Description
    Implements the LCD driver for the HD44780-compatible 16x2 character display
    on the EasyPIC v7 development board. The LCD is connected directly to PORTB
    in 4-bit mode (no SPI or I/O expander).

    EasyPIC v7 LCD Pin Connections (PIC18F45K42):
        RS (Register Select) : RB4  (LCD_RS)
        EN (Enable)          : RB5  (LCD_EN)
        D4 (Data bit 4)      : RB0  (LCD_D4)
        D5 (Data bit 5)      : RB1  (LCD_D5)
        D6 (Data bit 6)      : RB2  (LCD_D6)
        D7 (Data bit 7)      : RB3  (LCD_D7)
        R/W                  : GND  (write-only)

        Device                  :  PIC18F45K42
        Driver Version          :  3.00
        Compiler                :  XC8 2.00
        MPLAB                   :  MPLAB X 5.10
        System Clock            :  8 MHz (HFINTOSC)
 */

/*
    (c) 2017 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */
#include "lcd.h"
#include "mcc_generated_files/mcc.h"

/**
  Section: Macro Declarations
 */
#define LCD_CLEAR               0x01
#define LCD_HOME                0x02
#define LCD_ENTRY_MODE          0x06    /* increment, no display shift */
#define LCD_DISPLAY_ON          0x0C    /* display on, cursor off, blink off */
#define LCD_FUNCTION_SET_4BIT   0x28    /* 4-bit mode, 2 lines, 5x8 font */
#define LCD_SET_DDRAM_ADDRESS   0x80
#define LINE1_START_ADDRESS     0x80
#define LINE2_START_ADDRESS     0xC0

/**
  Section: Local Function Prototypes
 */
static void LCD_WriteNibble(uint8_t nibble);
static void LCD_EnablePulse(void);
static void LCD_WriteHalfByte(uint8_t nibble, uint8_t rs);

/**
  @Summary
    Writes a 4-bit nibble to LCD data lines D4-D7 (RB0-RB3).

  @Description
    Sets RB0-RB3 to the lower 4 bits of nibble. The nibble must be
    pre-shifted so that the desired 4 bits are in bits [3:0].
*/
static void LCD_WriteNibble(uint8_t nibble) {
    /* Drive each LCD data line from the corresponding nibble bit */
    if (nibble & 0x01) { LCD_D4_SetHigh(); } else { LCD_D4_SetLow(); }
    if (nibble & 0x02) { LCD_D5_SetHigh(); } else { LCD_D5_SetLow(); }
    if (nibble & 0x04) { LCD_D6_SetHigh(); } else { LCD_D6_SetLow(); }
    if (nibble & 0x08) { LCD_D7_SetHigh(); } else { LCD_D7_SetLow(); }
}

/**
  @Summary
    Generates an Enable pulse to latch data into the LCD.
*/
static void LCD_EnablePulse(void) {
    LCD_EN_SetHigh();
    __delay_us(1);      /* EN pulse width >= 450 ns */
    LCD_EN_SetLow();
    __delay_us(50);     /* Data hold time and command execution (most cmds < 37 us) */
}

/**
  @Summary
    Sends a full 8-bit value to the LCD in two 4-bit nibbles.

  @Param
    data - 8-bit value to send
    rs   - 0 for command register, 1 for data register
*/
static void LCD_WriteHalfByte(uint8_t data, uint8_t rs) {
    if (rs) { LCD_RS_SetHigh(); } else { LCD_RS_SetLow(); }

    /* Send high nibble (bits 7-4) first */
    LCD_WriteNibble(data >> 4);
    LCD_EnablePulse();

    /* Send low nibble (bits 3-0) */
    LCD_WriteNibble(data & 0x0F);
    LCD_EnablePulse();
}

/**
  Section: EasyPIC v7 LCD APIs
 */

/**
  @Summary
    Initializes the HD44780 LCD in 4-bit mode.

  @Description
    Follows the HD44780 initialization sequence for 4-bit mode as specified
    in the Hitachi HD44780U datasheet (Figure 24 - Initializing by Instruction).
    The EasyPIC v7 LCD is write-only (R/W tied to GND), so all timing is
    enforced with explicit delays.
*/
void LCD_Initialize(void) {
    /* Configure LCD PORTB pins as digital outputs */
    LCD_D4_SetDigitalOutput();
    LCD_D5_SetDigitalOutput();
    LCD_D6_SetDigitalOutput();
    LCD_D7_SetDigitalOutput();
    LCD_RS_SetDigitalOutput();
    LCD_EN_SetDigitalOutput();

    /* Ensure all LCD pins start low */
    LCD_RS_SetLow();
    LCD_EN_SetLow();
    LCD_D4_SetLow();
    LCD_D5_SetLow();
    LCD_D6_SetLow();
    LCD_D7_SetLow();

    /* Wait >40 ms after VDD rises to 4.5 V */
    __delay_ms(50);

    /*
     * HD44780 4-bit mode initialization sequence:
     * Three 0x3 writes in 8-bit mode, then switch to 4-bit.
     * During these writes RS=0, only the high nibble (D4-D7) matters.
     */

    /* Attempt 1: function set (8-bit), wait >4.1 ms */
    LCD_WriteNibble(0x03);
    LCD_EnablePulse();
    __delay_ms(5);

    /* Attempt 2: function set (8-bit), wait >100 us */
    LCD_WriteNibble(0x03);
    LCD_EnablePulse();
    __delay_us(200);

    /* Attempt 3: function set (8-bit), wait >100 us */
    LCD_WriteNibble(0x03);
    LCD_EnablePulse();
    __delay_us(200);

    /* Switch to 4-bit mode */
    LCD_WriteNibble(0x02);
    LCD_EnablePulse();
    __delay_us(200);

    /* From here all transfers are 8-bit sent as two 4-bit nibbles */

    /* Function set: 4-bit, 2 lines, 5x8 font */
    LCD_WriteCommand(LCD_FUNCTION_SET_4BIT);
    __delay_ms(1);

    /* Display off */
    LCD_WriteCommand(0x08);
    __delay_ms(1);

    /* Clear display */
    LCD_WriteCommand(LCD_CLEAR);
    __delay_ms(2);      /* Clear requires >1.52 ms */

    /* Entry mode: increment address, no display shift */
    LCD_WriteCommand(LCD_ENTRY_MODE);
    __delay_ms(1);

    /* Display on, cursor off, blink off */
    LCD_WriteCommand(LCD_DISPLAY_ON);
    __delay_ms(1);
}

void LCD_WriteCommand(uint8_t cmd) {
    LCD_WriteHalfByte(cmd, 0);  /* RS=0: command register */
}

void LCD_WriteByte(uint8_t data) {
    LCD_WriteHalfByte(data, 1); /* RS=1: data register */
}

void LCD_WriteString(const uint8_t *data) {
    uint8_t i = 0;
    while (data[i]) {
        LCD_WriteByte(data[i++]);
    }
}

void LCD_GoTo(uint8_t row, uint8_t column) {
    if (row < 2) {
        uint8_t pos = (row == 0) ? (LINE1_START_ADDRESS | column) : (LINE2_START_ADDRESS | column);
        LCD_WriteCommand(pos);
    }
}

void LCD_Clear(void) {
    LCD_WriteCommand(LCD_CLEAR);
    __delay_ms(2);      /* Clear requires >1.52 ms */
    LCD_GoTo(0, 0);
}
