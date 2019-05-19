/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Iotlabs_h
#define Iotlabs_h
 
#include "Arduino.h"
#include <WiFi.h>
 
class Iotlabs
{
  public:
    Iotlabs();
    void wifiConnection(String ssid, String pass);
    void setThingSpeak(String myTalkbackKey,String myWriteAPIKey);
    int sendThingSpeak(float *data,uint8_t sizeData,String &newCommand);
    int httpPOST(String postMessage, String &response);

  private:
    int _pin;
    WiFiClient  client;
    String postMessage;

    String _myTalkbackKey;
    String _myWriteAPIKey;

};
 
#endif