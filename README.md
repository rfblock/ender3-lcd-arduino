# ender3-lcd-arduino
This is a simple tutorial on how to reuse old LCD boards from Ender 3's with a microcontroller such as arduino or teensy

# Pinout
The entire board can be controlled via the EXP3 10-pin connector
The pinout on the EXP3 is as follows
```
        ------
BEEPER |10  9 | ENC
   EN1 | 8  7 | LCD_CS0(?)
   EN2   6  5 | LCD_SCK
LCD_CS | 4  3 | LCD_MOSI
   GND | 2  1 | 5V
        ------
```
Note that pins 6, 8, and 9 are floating when true, so use a pullup resistor to get a clean input

# Rotary Encoder + Button
The rotary encoder is standard incremental button/encoder and can be controlled with a library such as `Encoder.h`
The `ENC` pin (9) is for the built-in encoder button

# LCD
The Ender 3 LCD uses an ST7920 128x64 or equivalent driver.
A library, such as u8g2, can be used to control this
The `LCD_SCK` (5) is used for clock, `LCD_MOSI` (3) is used for data In/Out, and `LCD_CS` (4) is for Chip Select/Register Select
