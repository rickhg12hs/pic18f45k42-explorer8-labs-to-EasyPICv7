[![MCHP](images/microchip.png)](https://www.microchip.com)
# EasyPIC v7 Labs - PIC18F45K42

This project contains 11 labs for the **MikroElektronika EasyPIC v7** development board using a **PIC18F45K42** microcontroller in a 40-pin DIP socket. It is adapted from the original Microchip Explorer 8 Labs project.

## I. Introduction

The goal of this project is to demonstrate EasyPIC v7 board capabilities and the functionality of the PIC18F45K42 using 11 progressive labs. A state machine navigates between labs using the **S2 button** (RB7). A second button (**S1**, RB6) provides external stimulus for labs that require it. Lab output is shown on three PORTD LEDs (RD0–RD2, enabled via DIP switch SW3) and the on-board 16×2 LCD. Some labs use the on-board potentiometer (connected to RA0 via jumper J15) for analog input.

All labs are written in C and use MPLAB X IDE with the XC8 compiler. Peripheral configuration uses the MPLAB Code Configurator (MCC).

---

## II. Hardware Requirements

### A. EasyPIC v7 Development Board

- **Manufacturer:** MikroElektronika
- **Product page:** https://www.mikroe.com/easypic-v7
- **MCU:** PIC18F45K42 in the 40-pin DIP socket

### B. Required Jumper and DIP Switch Settings

| Setting | Configuration | Purpose |
|---------|---------------|---------|
| DIP switch SW3 (RD0, RD1, RD2) | ON | Enable LEDs on RD0, RD1, RD2 |
| Jumper J15 (RA0 position) | Connected | Connect potentiometer P1 to RA0 |
| LCD connector CN7 | Installed | Connect 16×2 character LCD |
| R/W on LCD | Tied to GND | LCD in write-only mode |

### C. Pin Mapping

| Signal | EasyPIC v7 Pin | Notes |
|--------|----------------|-------|
| LED_D6 | RD0 | PORTD LED, DIP switch SW3 position 1 |
| LED_D7 | RD1 | PORTD LED, DIP switch SW3 position 2 |
| LED_D8 | RD2 | PORTD LED, DIP switch SW3 position 3; also PWM output |
| SWITCH_S2 | RB7 | Navigate labs (active LOW, pull-up enabled) |
| SWITCH_S1 | RB6 | Lab stimulus (active LOW, pull-up enabled; IOC source) |
| Potentiometer | RA0 | Jumper J15 set to RA0 position |
| LCD RS | RB4 | HD44780 Register Select |
| LCD EN | RB5 | HD44780 Enable |
| LCD D4 | RB0 | HD44780 data bit 4 |
| LCD D5 | RB1 | HD44780 data bit 5 |
| LCD D6 | RB2 | HD44780 data bit 6 |
| LCD D7 | RB3 | HD44780 data bit 7 |

### D. Software Requirements

**Option A — MPLAB X IDE (traditional)**

| Tool | Version |
|------|---------|
| MPLAB X IDE | v5.15 or later |
| XC8 Compiler | v2.00 or later |
| MPLAB Code Configurator (MCC) | v3.75 or later |

Download: http://www.microchip.com/mplab/mplab-x-ide

**Option B — VS Code with MPLAB Extensions**

| Tool | Notes |
|------|-------|
| Visual Studio Code | Any recent version |
| MPLAB Extension Pack (`Microchip.mplab-extension-pack`) | Install from VS Code Marketplace |
| XC8 Compiler | v2.00 or later; install separately from Microchip |

Download XC8: https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers

---

## III. System Configuration

- **Clock:** Internal HFINTOSC at 8 MHz (no external crystal required)
- **Watchdog Timer:** Enabled via SWDTEN; ~8-second period (used in Lab 10)
- **LCD Interface:** HD44780 4-bit parallel mode (direct PORTB connection; no SPI or I/O expander)
- **PWM:** CCP2 output mapped to RD2 (LED_D8) via PPS during Lab 07

---

## IV. State Machine Flow

```
Power On → Welcome screen → Press S2 → Lab 1 → Press S2 → Lab 2 → ... → Lab 11 → Lab 1 (wrap)
```

- **S2 (RB7):** Press and release to advance to the next lab
- **S1 (RB6):** Used within labs as an external stimulus (press/hold)

---

## V. Lab Descriptions

### Lab 01 — Hello World
Turns on LED_D8 (RD2). LCD displays `Hello World` / `LED_D8 = ON`.
Demonstrates basic GPIO output configuration.

### Lab 02 — Blink
LED_D8 (RD2) blinks at ~1.5-second intervals using Timer1.
LCD alternates between `LED_D8 = OFF` and `LED_D8 = ON`.

### Lab 03 — Rotate
LEDs D6 (RD0), D7 (RD1), D8 (RD2) light up in sequence with a 500 ms software delay.
LCD shows `LED_Dx = ON` for the currently active LED.

### Lab 04 — ADC
Reads the potentiometer on RA0 (ADC channel 0). The top 3 MSBs of the 10-bit result
are displayed on the three LEDs. LCD shows `ADC Result = x` (0–7).
Demonstrates the ADCC peripheral.

### Lab 05 — Variable Speed Rotate (VSR)
Combines Lab 03 and Lab 04: LEDs rotate with speed controlled by the potentiometer.
LCD shows `Delay = xxx ms`.

### Lab 06 — Debounce
Each press of S1 (RB6) advances the lit LED one position (D6 → D7 → D8 → D6).
Holding S1 rotates continuously. LCD shows `LED_Dx = ON`.
Demonstrates software button debouncing.

### Lab 07 — PWM
Rotating the potentiometer adjusts the brightness of LED_D8 (RD2) via CCP2 PWM
(mapped to RD2 via PPS). LCD shows `Duty Cycle = xx%`.

### Lab 08 — Timers
Same visual output as Lab 03, but uses Timer1 for timing instead of software delay.
LCD shows `Time = xxx secs` (increments every ~1 second; resets at 100).

### Lab 09 — Interrupts
LEDs rotate at a constant speed. Pressing S1 (RB6) triggers an Interrupt-on-Change
(IOC) on the positive edge, reversing the rotation direction.
LCD shows `Direction: Right` or `Direction: Left`.

### Lab 10 — Sleep/Wake Up
LED_D7 (RD1) lights while the device counts down 5 seconds, then enters Sleep mode.
The Watchdog Timer wakes the device after ~8 seconds; LED_D6 and LED_D8 turn on,
LED_D7 turns off. LCD shows `I'm now awake!`.

### Lab 11 — EEPROM
Press S1 (RB6) to write the top 3 MSBs of the ADC result to EEPROM and display it
on the LEDs. Rotate the potentiometer to change the stored value.
LCD shows `Value = x`.

---

## VI. Building and Programming

### A. Using MPLAB X IDE

1. Open `pic18f45k42-explorer8-labs.X` in MPLAB X IDE.
2. Select **Project > Properties** and verify the XC8 compiler path.
3. Connect the EasyPIC v7 board to your PC using the on-board mikroProg USB programmer
   (or an external PICkit 3/ICD 3 via the RJ-12 connector).
4. Click **Make and Program Device** (F6).
5. After programming, press the Reset button on EasyPIC v7.
6. The LCD should display `Welcome / to EasyPIC v7`.
7. Press **S2** (RB7) to enter Lab 1.

### B. Using VS Code with MPLAB Extensions

#### Prerequisites

1. Install **Visual Studio Code**: https://code.visualstudio.com
2. Install the **XC8 compiler** (v2.00 or later) from
   https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers
3. In VS Code, open the Extensions view (**Ctrl+Shift+X**), search for
   **MPLAB Extension Pack**, and install `Microchip.mplab-extension-pack`.
   This installs all required components including the project importer,
   toolchain detector, language server, debugger adapter, and MCC.

> **If XC8 was installed after the MPLAB extensions:** open the Command
> Palette (**Ctrl+Shift+P**) and run **`MPLAB: Register Toolchains`**.
> This rescans for installed compilers and registers any that were added
> since the extension was first loaded.

#### Importing the Project

1. In VS Code, choose **File > Open Folder** (**Ctrl+K Ctrl+O**).
2. Navigate to and select the **`pic18f45k42-explorer8-labs.X`** folder
   (the MPLAB X project folder, not the repository root).
3. VS Code will detect the MPLAB X project and prompt you to import it.
   Accept the import — the **Project Importer for MPLAB** extension reads
   `nbproject/configurations.xml` and creates a `.vscode/` folder with
   a `mplab.json` configuration. Your original project files are not modified.

#### Building

- Press **Ctrl+Shift+B** or open the Command Palette and run
  **`MPLAB CMake: Full Build`**.
- Build output appears in the Terminal panel. A successful build produces
  `dist/free/production/pic18f45k42-explorer8-labs.X.production.hex`.

#### Configuring the Programmer

1. Open the Command Palette and run **`MPLAB: Edit Project Properties (UI)`**.
2. Under **Hardware Tool**, select your programmer (e.g., mikroProg, PICkit 3,
   ICD 3).
3. Confirm the **Device** is set to `PIC18F45K42` and the **Compiler** is `XC8`.

#### Programming the Device

1. Connect the EasyPIC v7 board via USB.
2. Open the **Run and Debug** view (**Ctrl+Shift+D**).
3. If no launch configuration exists, run **`Debug: Add Configuration`** and
   select **MPLAB Debugger**.
4. Press **F5** to build, program, and start a debug session, or use
   **`MPLAB: Make and Program Device`** from the Command Palette to program
   without debugging.
5. After programming, press the Reset button on EasyPIC v7.
6. The LCD should display `Welcome / to EasyPIC v7`.
7. Press **S2** (RB7) to enter Lab 1.

> **Note:** If you later modify project settings in MPLAB X IDE and the VS Code
> build becomes stale, delete `.vscode/mplab.json` and re-open the folder to
> trigger a fresh import.

---

## VII. Differences from Explorer 8 Version

| Feature | Explorer 8 (original) | EasyPIC v7 (this project) |
|---------|----------------------|--------------------------|
| LCD interface | SPI via MCP23S08 I/O expander | Direct HD44780 4-bit parallel |
| LCD pins | CS=RA2, SCK=RC3, SDO=RC5, SDI=RC4 | RS=RB4, EN=RB5, D4–D7=RB0–RB3 |
| LED pins | RB1 (D6), RB2 (D7), RB3 (D8) | RD0 (D6), RD1 (D7), RD2 (D8) |
| S1 button | RB0 (IOC) | RB6 (IOC) |
| S2 button | RA5 | RB7 |
| PWM output | CCP2 → RB3 | CCP2 → RD2 |
| Oscillator | External 8 MHz HS crystal | Internal HFINTOSC at 8 MHz |

---

## VIII. Troubleshooting

| Symptom | Check |
|---------|-------|
| LCD blank or garbage | Verify LCD contrast pot on EasyPIC v7; check PORTB RB0–RB5 connections |
| LEDs not lighting | Confirm DIP switch SW3 positions 1–3 (RD0–RD2) are ON |
| Buttons unresponsive | Verify buttons are connected to RB6 (S1) and RB7 (S2); pull-ups enabled |
| Potentiometer has no effect | Check jumper J15 is set to RA0 position |
| PWM lab has no dimming | Confirm DIP switch SW3 position 3 (RD2) is ON |

---

*Adapted from [Microchip pic18f45k42-explorer8-labs](https://github.com/microchip-pic-avr-examples/pic18f45k42-explorer8-labs) for the MikroElektronika EasyPIC v7 board.*
