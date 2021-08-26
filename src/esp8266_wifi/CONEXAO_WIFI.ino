#include <ESP8266WiFi.h>  
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

char ssid[] = "";    
char pass[] = "";      


void setup() {
  Serial.begin(115200);
 
  while (!Serial); 
   
    WiFi.begin(ssid, pass); 
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi conectado"); 
    Serial.println(WiFi.localIP());
}
    
void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { 
  
      WiFiClient client;
      HTTPClient http;

      String serverPath = "http://";
  
      http.begin(client,serverPath.c_str()); 
      int httpCode = http.GET();                                        
  
      if (httpCode > 0) { 
  
          String payload = http.getString();
          Serial.println(httpCode);
          Serial.println(payload);
        }
  
      else {
        Serial.println("Error on HTTP request");
      }
  
      http.end(); 
    }
  
    delay(10000);
}
