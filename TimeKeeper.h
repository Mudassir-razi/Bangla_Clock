#ifndef TimeKeeper_h
#define TimeKeeper_h

#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <HTTPClient.h>
#include <Arduino_JSON.h>


class TimeKeeper {

private:
  int banglamonth;
  int bangladay;
  String jsonBuffer;
  String openWeatherMapApiKey;
  const char* ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 21600;
  const int daylightOffset_sec = 0;

  String httpGETRequest(const char* serverName);
  int _conv();


public:
  String city = "Dhaka";
  String country_code = "BD";
  TimeKeeper();
  double getTemp();
  double getHumidity();
  double getFeelslike();
  int getMonth();
  int getDay();
  int getHour();
  int getMin();
};

#endif
