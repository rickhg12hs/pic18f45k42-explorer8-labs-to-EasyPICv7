/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F45K42
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10

  @Notes
    Adapted for EasyPIC v7 development board.
    PIC18F45K42 in 40-pin DIP socket.

    EasyPIC v7 Pin Mapping:
      LED_D6     : RD0  (PORTD, DIP switch SW3 enabled)
      LED_D7     : RD1  (PORTD, DIP switch SW3 enabled)
      LED_D8     : RD2  (PORTD, DIP switch SW3 enabled; also PWM output)
      SWITCH_S1  : RB6  (active LOW, pull-up; IOC on positive edge)
      SWITCH_S2  : RB7  (active LOW, pull-up)
      POT_CHANNEL: RA0  (analog; connect via jumper J15)
      LCD_RS     : RB4  (HD44780 Register Select)
      LCD_EN     : RB5  (HD44780 Enable)
      LCD_D4     : RB0  (HD44780 data bit 4)
      LCD_D5     : RB1  (HD44780 data bit 5)
      LCD_D6     : RB2  (HD44780 data bit 6)
      LCD_D7     : RB3  (HD44780 data bit 7)
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set POT_CHANNEL aliases (RA0 - same as Explorer 8; connect via J15 jumper)
#define POT_CHANNEL_TRIS                 TRISAbits.TRISA0
#define POT_CHANNEL_LAT                  LATAbits.LATA0
#define POT_CHANNEL_PORT                 PORTAbits.RA0
#define POT_CHANNEL_WPU                  WPUAbits.WPUA0
#define POT_CHANNEL_OD                   ODCONAbits.ODCA0
#define POT_CHANNEL_ANS                  ANSELAbits.ANSELA0
#define POT_CHANNEL_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define POT_CHANNEL_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define POT_CHANNEL_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define POT_CHANNEL_GetValue()           PORTAbits.RA0
#define POT_CHANNEL_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define POT_CHANNEL_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define POT_CHANNEL_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define POT_CHANNEL_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define POT_CHANNEL_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define POT_CHANNEL_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define POT_CHANNEL_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define POT_CHANNEL_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set SWITCH_S2 aliases (RB7 - EasyPIC v7 push button, active LOW)
#define SWITCH_S2_TRIS                 TRISBbits.TRISB7
#define SWITCH_S2_LAT                  LATBbits.LATB7
#define SWITCH_S2_PORT                 PORTBbits.RB7
#define SWITCH_S2_WPU                  WPUBbits.WPUB7
#define SWITCH_S2_OD                   ODCONBbits.ODCB7
#define SWITCH_S2_ANS                  ANSELBbits.ANSELB7
#define SWITCH_S2_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define SWITCH_S2_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define SWITCH_S2_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define SWITCH_S2_GetValue()           PORTBbits.RB7
#define SWITCH_S2_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define SWITCH_S2_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define SWITCH_S2_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define SWITCH_S2_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define SWITCH_S2_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define SWITCH_S2_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define SWITCH_S2_SetAnalogMode()      do { ANSELBbits.ANSELB7 = 1; } while(0)
#define SWITCH_S2_SetDigitalMode()     do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set SWITCH_S1 aliases (RB6 - EasyPIC v7 push button, active LOW, IOC source)
#define SWITCH_S1_TRIS                 TRISBbits.TRISB6
#define SWITCH_S1_LAT                  LATBbits.LATB6
#define SWITCH_S1_PORT                 PORTBbits.RB6
#define SWITCH_S1_WPU                  WPUBbits.WPUB6
#define SWITCH_S1_OD                   ODCONBbits.ODCB6
#define SWITCH_S1_ANS                  ANSELBbits.ANSELB6
#define SWITCH_S1_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define SWITCH_S1_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define SWITCH_S1_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define SWITCH_S1_GetValue()           PORTBbits.RB6
#define SWITCH_S1_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define SWITCH_S1_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define SWITCH_S1_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define SWITCH_S1_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define SWITCH_S1_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define SWITCH_S1_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define SWITCH_S1_SetAnalogMode()      do { ANSELBbits.ANSELB6 = 1; } while(0)
#define SWITCH_S1_SetDigitalMode()     do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set LED_D6 aliases (RD0 - EasyPIC v7 PORTD LED, enable via DIP switch SW3)
#define LED_D6_TRIS                 TRISDbits.TRISD0
#define LED_D6_LAT                  LATDbits.LATD0
#define LED_D6_PORT                 PORTDbits.RD0
#define LED_D6_WPU                  WPUDbits.WPUD0
#define LED_D6_OD                   ODCONDbits.ODCD0
#define LED_D6_ANS                  ANSELDbits.ANSELD0
#define LED_D6_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define LED_D6_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define LED_D6_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define LED_D6_GetValue()           PORTDbits.RD0
#define LED_D6_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define LED_D6_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define LED_D6_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define LED_D6_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define LED_D6_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define LED_D6_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define LED_D6_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define LED_D6_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set LED_D7 aliases (RD1 - EasyPIC v7 PORTD LED, enable via DIP switch SW3)
#define LED_D7_TRIS                 TRISDbits.TRISD1
#define LED_D7_LAT                  LATDbits.LATD1
#define LED_D7_PORT                 PORTDbits.RD1
#define LED_D7_WPU                  WPUDbits.WPUD1
#define LED_D7_OD                   ODCONDbits.ODCD1
#define LED_D7_ANS                  ANSELDbits.ANSELD1
#define LED_D7_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define LED_D7_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define LED_D7_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define LED_D7_GetValue()           PORTDbits.RD1
#define LED_D7_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define LED_D7_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define LED_D7_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define LED_D7_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define LED_D7_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define LED_D7_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define LED_D7_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define LED_D7_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set LED_D8 aliases (RD2 - EasyPIC v7 PORTD LED, enable via DIP switch SW3; also PWM output)
#define LED_D8_TRIS                 TRISDbits.TRISD2
#define LED_D8_LAT                  LATDbits.LATD2
#define LED_D8_PORT                 PORTDbits.RD2
#define LED_D8_WPU                  WPUDbits.WPUD2
#define LED_D8_OD                   ODCONDbits.ODCD2
#define LED_D8_ANS                  ANSELDbits.ANSELD2
#define LED_D8_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define LED_D8_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define LED_D8_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define LED_D8_GetValue()           PORTDbits.RD2
#define LED_D8_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define LED_D8_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define LED_D8_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define LED_D8_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define LED_D8_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define LED_D8_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define LED_D8_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define LED_D8_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set LCD_D4 aliases (RB0 - HD44780 data bit 4)
#define LCD_D4_TRIS                 TRISBbits.TRISB0
#define LCD_D4_LAT                  LATBbits.LATB0
#define LCD_D4_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define LCD_D4_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define LCD_D4_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)

// get/set LCD_D5 aliases (RB1 - HD44780 data bit 5)
#define LCD_D5_TRIS                 TRISBbits.TRISB1
#define LCD_D5_LAT                  LATBbits.LATB1
#define LCD_D5_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define LCD_D5_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define LCD_D5_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)

// get/set LCD_D6 aliases (RB2 - HD44780 data bit 6)
#define LCD_D6_TRIS                 TRISBbits.TRISB2
#define LCD_D6_LAT                  LATBbits.LATB2
#define LCD_D6_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define LCD_D6_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define LCD_D6_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)

// get/set LCD_D7 aliases (RB3 - HD44780 data bit 7)
#define LCD_D7_TRIS                 TRISBbits.TRISB3
#define LCD_D7_LAT                  LATBbits.LATB3
#define LCD_D7_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define LCD_D7_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define LCD_D7_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)

// get/set LCD_RS aliases (RB4 - HD44780 Register Select)
#define LCD_RS_TRIS                 TRISBbits.TRISB4
#define LCD_RS_LAT                  LATBbits.LATB4
#define LCD_RS_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define LCD_RS_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define LCD_RS_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)

// get/set LCD_EN aliases (RB5 - HD44780 Enable)
#define LCD_EN_TRIS                 TRISBbits.TRISB5
#define LCD_EN_LAT                  LATBbits.LATB5
#define LCD_EN_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define LCD_EN_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define LCD_EN_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF6 pin functionality (SWITCH_S1 on RB6)
 * @Example
    IOCBF6_ISR();
 */
void IOCBF6_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF6 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF6 at application runtime

  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF6_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF6_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF6 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF6_SetInterruptHandler() method.
    This handler is called every time the IOCBF6 ISR is executed and allows any function to be registered at runtime.

  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF6_SetInterruptHandler(IOCBF6_InterruptHandler);

*/
extern void (*IOCBF6_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF6 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF6_SetInterruptHandler() method.
    This handler is called every time the IOCBF6 ISR is executed.

  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF6_SetInterruptHandler(IOCBF6_DefaultInterruptHandler);

*/
void IOCBF6_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/
