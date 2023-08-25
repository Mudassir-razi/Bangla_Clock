#include <Adafruit_BusIO_Register.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

/*********************************************************************
                         Arduino VGA library.

                      https://simple-circuit.com/

This library is based on VGAX Library:
https://github.com/smaffer/vgax

*********************************************************************/

#ifndef _VGA_H
#define _VGA_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
#endif


#define BLACK 0
#define WHITE 1

#define VGAWIDTH    160
//#define VGAHEIGHT   80
#define VGAHEIGHT   80

#define CLONED_LINES  5
#define STARTLINE    50   // start line
#define ENDLINE   (STARTLINE + VGAHEIGHT * CLONED_LINES)  // end line
#define VGA_BWIDTH   20   //number of bytes in a row ( = VGAWIDTH/8 )



class VGA : public Adafruit_GFX {
  public:
    VGA();

    void begin();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void clearDisplay(void);
    static void delay(uint16_t msec);
};

#endif
