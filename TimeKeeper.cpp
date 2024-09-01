#include "TimeKeeper.h"

TimeKeeper::TimeKeeper() {
  banglamonth = -1;
  bangladay = -1;
  jsonBuffer;
  openWeatherMapApiKey = "cf46eaa183133c570aa98dcc4215c472";
}

String TimeKeeper:: httpGETRequest(const char* serverName) {
    WiFiClient client;
    HTTPClient http;

    //Domain name with URL path or IP address with path
    http.begin(client, serverName);

    // Send HTTP POST request
    int httpResponseCode = http.GET();

    String payload = "{}";

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      payload = http.getString();
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

    return payload;
  }

int TimeKeeper :: _conv() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time");
      return -1;
    }
    //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    int _month = timeinfo.tm_mon;
    int _day = timeinfo.tm_mday;

    if (_month == 0) {
      
      if (_day <= 13) banglamonth = 8, bangladay = _day + 17;
      else banglamonth = 9, bangladay = _day - 13;
    } else if (_month == 1) {
      if (_day <= 12) banglamonth = 9, bangladay = _day + 18;
      else banglamonth = 10, bangladay = _day - 12;
    } else if (_month == 2) {
      if (_day <= 14) banglamonth = 10, bangladay = _day + 16;
      else banglamonth = 11, bangladay = _day - 14;
    } else if (_month == 3) {
      if (_day <= 13) banglamonth = 11, bangladay = _day + 17;
      else banglamonth = 0, bangladay = _day - 13;
    } else if (_month == 4) {
      if (_day <= 13) banglamonth = 0, bangladay = _day + 17;
      else banglamonth = 1, bangladay = _day - 13;
    } else if (_month == 5) {
      if (_day <= 14) banglamonth = 1, bangladay = _day + 17;
      else banglamonth = 2, bangladay = _day - 14;
    } else if (_month == 6) {
      if (_day <= 15) banglamonth = 2, bangladay = _day + 16;
      else banglamonth = 3, bangladay = _day - 15;
    } else if (_month == 7) {
      if (_day <= 15) banglamonth = 3, bangladay = _day + 16;
      else banglamonth = 4, bangladay = _day - 15;
    } else if (_month == 8) {
      if (_day <= 15) banglamonth = 4, bangladay = _day + 16;
      else banglamonth = 5, bangladay = _day - 15;
    } else if (_month == 9) {
      if (_day <= 15) banglamonth = 5, bangladay = _day + 15;
      else banglamonth = 6, bangladay = _day - 15;
    } else if (_month == 10) {
      if (_day <= 14) banglamonth = 6, bangladay = _day + 16;
      else banglamonth = 7, bangladay = _day - 14;
    } else {
      if (_day <= 14) banglamonth = 7, bangladay = _day + 16;
      else banglamonth = 8, bangladay = _day - 14;
    }
    //Serial.printf("%d %d\n", banglamonth, bangladay);
    return _month * 100 + _day;
  }


double TimeKeeper::getTemp() {
  String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country_code + "&APPID=" + openWeatherMapApiKey;

  jsonBuffer = httpGETRequest(serverPath.c_str());
  JSONVar myObject = JSON.parse(jsonBuffer);

  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return -500;
  }
  double temp = myObject["main"]["temp"];
  //Serial.println(temp);
  return temp;
}
double TimeKeeper::getHumidity() {
  String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country_code + "&APPID=" + openWeatherMapApiKey;

  jsonBuffer = httpGETRequest(serverPath.c_str());
  JSONVar myObject = JSON.parse(jsonBuffer);

  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return -500;
  }
  double humidity = myObject["main"]["humidity"];
  return humidity;
}

double TimeKeeper::getFeelslike() {
  String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country_code + "&APPID=" + openWeatherMapApiKey;

  jsonBuffer = httpGETRequest(serverPath.c_str());
  JSONVar myObject = JSON.parse(jsonBuffer);

  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return -500;
  }
  double temp = myObject["main"]["feel_like"];
  return temp;
}

int TimeKeeper::getMonth() {
  int temp = _conv();
  return temp / 100;
}
int TimeKeeper::getDay() {
  int temp = _conv();
  return temp % 100;
}

int TimeKeeper::getHour() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain hour");
    return -1;
  }

  return timeinfo.tm_hour;
}


int TimeKeeper::getMin() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain min");
    return -1;
  }
  return timeinfo.tm_min;
}
