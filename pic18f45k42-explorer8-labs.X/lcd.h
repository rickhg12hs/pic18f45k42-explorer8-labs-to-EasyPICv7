/**
  EasyPIC v7 LCD Header File

  @Company
    Microchip Technology Inc.

  @File Name
    lcd.h

  @Summary
    HD44780 4-bit parallel LCD driver header for EasyPIC v7.

  @Description
    This header file provides APIs for the EasyPIC v7 LCD (HD44780-compatible,
    16x2 character display) connected directly to PORTB in 4-bit mode.

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


#ifndef LCD_H
#define	LCD_H

/**
  Section: Included Files
 */
#include <stdint.h>

/**
  Section: EasyPIC v7 LCD Function Prototypes
 */
void LCD_Initialize(void);
void LCD_WriteCommand(uint8_t cmd);
void LCD_WriteByte(uint8_t data);
void LCD_WriteString(const uint8_t *data);
void LCD_GoTo(uint8_t row, uint8_t column);
void LCD_Clear(void);

#endif	/* LCD_H */
