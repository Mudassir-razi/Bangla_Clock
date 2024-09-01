//This example shows how to use different fonts on a VGA screen.
//You need to connect a VGA screen cable to the pins specified below.
//cc by-sa 4.0 license
//bitluni

#include "ESP32Lib.h"
#include <Ressources/Font6x8.h>
#include "CustomBangla.h"
#include <WiFi.h>
#include "TimeKeeper.h"

const char* ssid       = "Janina";
const char* password   = "nijerdatakin";

//pin configuration
const int redPin = 14;
const int greenPin = 19;
const int bluePin = 27;
const int hsyncPin = 32;
const int vsyncPin = 33;

//VGA Device
VGA3Bit vga;

//timer
TimeKeeper time_keeper;

int now,hour = 0, minutes = 0, seconds = 0;
int day = 0, month = 0, year = 2023;
int temp = 0;

void setup()
{
  //collect all data--------------------------------------------------
  //digitalWrite(13,HIGH);
  //delay(1000);
  WiFi.begin(ssid, password);
  digitalWrite(13,LOW);
  delay(1000);
  
  if(WiFi.status()==WL_CONNECTED)
  {
    digitalWrite(13,HIGH);
    delay(1000);
  }
  month = time_keeper.getMonth();
  day = time_keeper.getDay();
  hour = time_keeper.getHour();
  minutes = time_keeper.getMin();




  char *log;
  //initializing vga at the specified pins
	vga.init(vga.MODE200x150, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
	vga.setTextColor(vga.RGB(255, 255, 255), vga.RGB(0, 0, 0));
  vga.setFont(Font6x8);

  vga.clear();
  //vga.print("n ");
  /*
  vga.cursorX = 20;
  vga.cursorY = 20;
  */
}

void loop()
{
  if(!(millis()%1000))
  {
    ++seconds;
    if(seconds == 60) 
    {
      ++minutes;
      seconds = 0;
    }
    if(minutes == 60) 
    {
      ++hour;
      minutes = 0;
    }

    //----------------------------------time
    vga.clear(0);
    vga.setCursor(0, 0);
    vga.print(hour);
    vga.print(":");
    vga.print(minutes);
    vga.print(":");
    vga.print(seconds);
    vga.println();

    //---------------------------------date
    vga.print(date);
    vga.print("/");
    vga.print(month);
    vga.print("/");
    vga.print(year);
  }
}