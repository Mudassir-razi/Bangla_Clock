
/*************************************************************************
 * 
 * VGA output with Arduino (white and black colors).
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 *
 ************************************************************************/

#include <Adafruit_GFX.h>  // include Adafruit graphics library
#include "CustomBangla.h"
//#include "TomThumbBangla.h"
#include "VGA.h"           // include VGA library 

// initialize the VGA library
VGA display = VGA();


void setup(void) {
  // initialize the VGA display
   display.begin();
 
  display.delay(5000);     // wait 5 seconds
  display.clearDisplay();  // clear the screen buffer
  display.setCursor(0,50);
  display.setTextSize(1);
  display.setFont(&CustomBangla);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("sNBr");
 
  display.println("AMr IIk");
  display.println("Mrb{%");
  
  
  //display.setFont(&TomThumb);
  //display.setTextColor(BLACK, WHITE);
  //display.println(3.141592);
  //display.setTextColor(WHITE);
  //display.print("Bangla Clock 2.0");
  //display.println(0xDEADBEEF, HEX);
 
  display.setCursor(0, 40);
  //display.setTextSize(1);
  //display.print("0123456789");
  
}

void loop() {

}

// end of code.

/*
#define hFrontPorch 1
#define hBackPorch 2.2
#define vFrontPorch 26.4
#define vBackPorch 607 
#define visibleLines 15840
#define visiblePixels 20
#define hSyncPulse 3.2
#define vSyncPulse 105.6

int hSync = 13;
int vSync = 12;
int deltaTimeV, deltaTimeH;
int oldTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(hSync, OUTPUT);
  pinMode(vSync, OUTPUT);

  deltaTimeV = 0;
  deltaTimeH = 0;
  oldTime = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(deltaTimeH >= visiblePixels && deltaTimeH < (visiblePixels + hFrontPorch + hSyncPulse + hBackPorch))digitalWrite(hSync, 1);
  else digitalWrite(hSync, 0);

  if(deltaTimeV >= visibleLines && deltaTimeV < (visibleLines + vFrontPorch + vSyncPulse + vBackPorch))digitalWrite(vSync, 1);
  else digitalWrite(vSync, 0);


  if(deltaTimeH > 26.4)deltaTimeH = 0;
  if(deltaTimeV > 16579)deltaTimeV = 0;
  calculateDeltaTime();

}

void calculateDeltaTime()
{
  int currentTime = micros();
  int deltaTime = currentTime - oldTime;
  oldTime = currentTime;
  deltaTimeV += deltaTime;
  deltaTimeH += deltaTime;
}
*/