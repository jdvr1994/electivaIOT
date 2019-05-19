#include <Iotlabs.h>

Iotlabs iot;

char cSSID[32];
char cPass[20];


void setup() {
  Serial.begin(115200);
  iot.wifiConnection("ARTURO VELAZQUEZ","eliecer1908");
  //Set (Talkback API Key , Channel Write API Key)
  iot.setThingSpeak("3NUA2OV628IFEXUM","05X1LKWUCXF89EMS");
}

void loop() {
  float datos[4] = {1.55,554,654.564,1.223};
  
  String newCommand = String();
  int code = iot.sendThingSpeak(datos,4,newCommand);
  Serial.println(code);Serial.println(newCommand);
  delay(20000);
}

