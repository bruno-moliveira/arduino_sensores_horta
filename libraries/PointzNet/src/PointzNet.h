
/*
library for pointznet.com
Compatible with ESP8266

Created by : pointznet tech. team
Date : 2017.Aug.24
updated :2017.Aug.27, 12:15
updated :2017.Aug.27, 15:00
updated : 2017.Oct.18, 1818
*/

#ifndef pointznet_h
#define pointznet_h

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "ArduinoJson.h"

class pointznet
{

public:
  bool begin(const char *ssid, const char *passw);
  String Senddata(const char *username, float d0, float d1, String lat, String lng);
  String Sendnotify(const char *username, String message);
  String ReadAQI(String mode, String lat, String lng, String radius);
  String getVersion();

private:
  const char *_ssid, *_passw;
  float _d0, _d1;
  String _lat, _lng;
  const char *_username;
  String _message;
  String _str;
  String _response, _responseNotify;
  String _mode;
  String _radius;
  String _respaqi;
  const char *_libversion;
};

#endif
