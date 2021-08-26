
/*
lib for pointznet iot device
Compatible only ESP8266

Created by : pointznet tech. team
Date : 2017.Aug.24
updated :2017.Aug.27, 12:15
updated :2017.Aug.27, 15:00
updated : 2017.Oct.18, 1818
*/

#include "pointznet.h"

#define pointznet_HOST "35.197.148.121"
#define pointznet_PORT 80
#define pointznet_libVersion "v0.5 Beta"

//Connect WiFi router
bool pointznet::begin(const char *ssid, const char *passw)
{
    //Transfer variable
    _ssid = ssid;
    _passw = passw;
  int _cnt=0, _retry=30;
  bool _conn = false;

  //Connect WiFi
  WiFi.begin(_ssid,_passw);
  Serial.print("pointznet wifi start connection...");

  //Connecting WiFi
  while ((WiFi.status() != WL_CONNECTED) && (_cnt <= _retry))
  {
    delay(500);
    Serial.print(".");
    _cnt++;
  }

  if(WiFi.status() == WL_CONNECTED)
  {
    _conn = true;
    Serial.println("\nWiFi for pointznet Connected !");
  }else{
    _conn = false;
  }

  return _conn;
}

String pointznet::Senddata(const char *username, float d0, float d1, String lat, String lng)
{
    //Transfer variable
    _username = username;
    _d0 = d0;
    _d1 = d1;
    _lat = lat;
    _lng = lng;

    //Create connection TCP to pointznet
    WiFiClient client;

    if (client.connect(pointznet_HOST, pointznet_PORT))
    {
      //Start sending data package
      _str = "GET /src/php/iot_user.php?username=";
      _str += _username;
      _str += "&d0=";
      _str += _d0;
      _str += "&d1=";
      _str += _d1;
      _str += "&lat=";
      _str += _lat;
      _str += "&lng=";
      _str += _lng;
      _str += " HTTP/1.1\r\n";
      _str += "Host: 35.197.148.121\r\n";
      _str += "Connection: keep-alive\r\n\r\n";

      //Push data
      client.print(_str);

      //Check response back
      while(client.available()){
        _response = client.readStringUntil('\r');
      }

      return _response;
    }
}

String pointznet::Sendnotify(const char *username, String message)
{
    // Transfer variable
    _username = username;
    _message = message;
    _message.replace(" ","%20");

    WiFiClient client;

    if (client.connect(pointznet_HOST, pointznet_PORT))
    {
      //Start sending data package
      _str = "GET /src/php/iot_notify.php?iotaddr=";
      _str += _username;
      _str += "&message=";
      _str += _message;
      _str += " HTTP/1.1\r\n";
      _str += "Host: 35.197.148.121\r\n";
      _str += "Connection: keep-alive\r\n\r\n";

      //Push data
      client.print(_str);

      //Check response back
      while(client.available()){
        _responseNotify = client.readStringUntil('\r');
      }

      return _responseNotify;
    }

}

String pointznet::ReadAQI(String mode, String lat, String lng, String radius)
{
    // Transfer variable
    _mode = mode;
    _lat = lat;
    _lng = lng;
    _radius = radius;

    WiFiClient client;

    if (client.connect(pointznet_HOST, pointznet_PORT))
    {
      //Start sending data package
      _str = "GET /aqicn/aqicn_src/php/aqicn_api.php?mode=";
      _str += _mode;
      _str += "&lat=";
      _str += _lat;
      _str += "&lng=";
      _str += _lng;
      _str += "&radius=";
      _str += _radius;
      _str += " HTTP/1.1\r\n";
      _str += "Host: 35.197.148.121\r\n";
      _str += "Connection: keep-alive\r\n\r\n";

      //Push data
      client.print(_str);

      //Wait for PHP execution.
      delay(2500);

      //Check response back
      while(client.available()){
        _respaqi = client.readStringUntil('\r');
      }

      return _respaqi;
    }

}

/* Pointznet library version */
String pointznet::getVersion()
{
  return pointznet_libVersion;
}
