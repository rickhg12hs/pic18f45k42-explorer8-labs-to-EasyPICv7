/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F45K42
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB             :  MPLAB X 5.10

  Notes:
    Adapted for EasyPIC v7 development board.
    - LEDs moved from PORTB (RB1-RB3) to PORTD (RD0-RD2)
    - Buttons moved: S1 from RB0 to RB6, S2 from RA5 to RB7
    - LCD pins on PORTB (RB0-RB5) for direct HD44780 4-bit parallel interface
    - SPI1 PPS removed (LCD no longer uses SPI/I2C expander)
    - IOC moved from IOCBF0 to IOCBF6 (S1 button now on RB6)

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

#include "pin_manager.h"


void (*IOCBF6_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    PORTA: RA0 = input (POT analog), rest inputs
    PORTB: RB0-RB5 = output (LCD), RB6 = input (S1), RB7 = input (S2)
    PORTC: all inputs (unused)
    PORTD: RD0-RD2 = output (LEDs), rest inputs
    PORTE: inputs
    */
    TRISE = 0x07;
    TRISA = 0xFF;   // All PORTA inputs (RA0 = POT analog input)
    TRISB = 0xC0;   // RB0-RB5 output (LCD), RB6 input (S1), RB7 input (S2)
    TRISC = 0xFF;   // All PORTC inputs (unused)
    TRISD = 0xF8;   // RD0-RD2 output (LEDs D6/D7/D8), RD3-RD7 inputs

    /**
    ANSELx registers
    Only RA0 is analog (potentiometer); all others digital
    */
    ANSELD = 0x00;  // PORTD all digital (LEDs are digital outputs)
    ANSELC = 0x00;  // PORTC all digital
    ANSELB = 0x00;  // PORTB all digital (LCD + buttons)
    ANSELE = 0x07;
    ANSELA = 0xFE;  // RA0 analog (POT), rest digital (0b11111110)

    /**
    WPUx registers
    Enable pull-ups on RB6 (S1) and RB7 (S2) — buttons are active LOW
    */
    WPUD = 0x00;
    WPUE = 0x00;
    WPUB = 0xC0;   // Enable pull-ups on RB6 and RB7
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    RxyI2C registers - disable I2C slew rate control on all pins
    */
    RB1I2C = 0x00;
    RB2I2C = 0x00;
    RC3I2C = 0x00;
    RC4I2C = 0x00;
    RD0I2C = 0x00;
    RD1I2C = 0x00;

    /**
    ODx registers
    */
    ODCONE = 0x00;
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    ODCOND = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x07;


    /**
    IOCx registers - Interrupt on Change for SWITCH_S1 (RB6, positive edge)
    */
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF6 = 0;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN6 = 0;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP6 = 1;

    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCBF6_SetInterruptHandler(IOCBF6_DefaultInterruptHandler);

    // Enable IOCI interrupt
    PIE0bits.IOCIE = 1;

    // Note: SPI1 PPS removed - LCD now uses direct parallel interface (HD44780 4-bit mode)
}

void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin IOCBF6 (SWITCH_S1 on RB6)
    if(IOCBFbits.IOCBF6 == 1)
    {
        IOCBF6_ISR();
    }
}

/**
   IOCBF6 Interrupt Service Routine (SWITCH_S1 on RB6)
*/
void IOCBF6_ISR(void) {

    // Add custom IOCBF6 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF6_InterruptHandler)
    {
        IOCBF6_InterruptHandler();
    }
    IOCBFbits.IOCBF6 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF6 at application runtime
*/
void IOCBF6_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF6_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF6
*/
void IOCBF6_DefaultInterruptHandler(void){
    // add your IOCBF6 interrupt custom code
    // or set custom function using IOCBF6_SetInterruptHandler()
}

/**
 End of File
*/
