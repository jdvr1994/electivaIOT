
/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
 
#include "Arduino.h"
#include "Iotlabs.h"
#include <WiFi.h>


Iotlabs::Iotlabs(){

}
 
void Iotlabs::wifiConnection(String ssid, String pass){
  char cSSID[32];
  char cPass[20];
  //-------- Conexion con la red de WIFI -----------
   ssid.toCharArray(cSSID,32);
   pass.toCharArray(cPass,20);

   WiFi.begin(cSSID, cPass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void Iotlabs::setThingSpeak(String myTalkbackKey,String myWriteAPIKey){
    _myTalkbackKey = myTalkbackKey;
    _myWriteAPIKey = myWriteAPIKey;
}

int Iotlabs::sendThingSpeak(float *data,uint8_t sizeData,String &newCommand){
  postMessage = String();
  for(uint8_t i=0;i<sizeData;i++){
    if(i>0) postMessage += String("&");
    postMessage += String("field")+String(i+1)+String("=") + String(data[i]);
  }

  postMessage +=  String("&api_key=") + _myWriteAPIKey +
                  String("&talkback_key=") + _myTalkbackKey;  

  Serial.println(postMessage);
  // make the POST to ThingSpeak
  int x = httpPOST(postMessage, newCommand);
  client.stop();
  
  return x;
}


int Iotlabs::httpPOST(String postMessage, String &response){

  bool connectSuccess = false;
  connectSuccess = client.connect("api.thingspeak.com",80);

  if(!connectSuccess){
      return -301;   
  }
  
  postMessage += "&headers=false";
  
  String Headers =  String("POST /update HTTP/1.1\r\n") +
                    String("Host: api.thingspeak.com\r\n") +
                    String("Content-Type: application/x-www-form-urlencoded\r\n") +
                    String("Connection: close\r\n") +
                    String("Content-Length: ") + String(postMessage.length()) +
                    String("\r\n\r\n");

  client.print(Headers);
  client.print(postMessage);

  long startWaitForResponseAt = millis();
  while(client.available() == 0 && millis() - startWaitForResponseAt < 5000){
      delay(100);
  }

  if(client.available() == 0){       
    return -304; // Didn't get server response in time
  }

  if(!client.find(const_cast<char *>("HTTP/1.1"))){
      return -303; // Couldn't parse response (didn't find HTTP/1.1)
  }
  
  int status = client.parseInt();
  if(status != 200){
    return status;
  }

  if(!client.find(const_cast<char *>("\n\r\n"))){
    return -303;
  }

  String tempString = String(client.readString());
  response = tempString;
  
  return status;
    
}