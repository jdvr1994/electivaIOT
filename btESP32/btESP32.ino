#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "BluetoothSerial.h" 
BluetoothSerial BT;

int btRead;
int LED_BUILTIN = 2;

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

void setup() {
  Serial.begin(115200);
  Serial.println(F("BME280 test"));
  BT.begin("IOT_LABS");
  Serial.println("El Dispositivo esta listo para emparejar");

  pinMode (LED_BUILTIN, OUTPUT);

  //---------- SENSOR -----------
  bool status;
    
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
  //------------- FIN SENSOR ----------------
}

void loop() {
  
  if (BT.available())
  {
      btRead = BT.read();
      Serial.print("Recibido:"); Serial.println(btRead);
  
      if (btRead == 49){
          digitalWrite(LED_BUILTIN, HIGH);
          BT.println("LED turned ON");
      }
          
      if (btRead == 48){
          digitalWrite(LED_BUILTIN, LOW);
          BT.println("LED turned OFF");
      }     

      if(btRead == 50)printValues();
  }
  delay(20);
}

void printValues() {
    BT.print("Temperature = ");
    BT.print(bme.readTemperature());
    BT.println(" *C");

    BT.print("Pressure = ");
    BT.print(bme.readPressure() / 100.0F);
    BT.println(" hPa");

    BT.print("Approx. Altitude = ");
    BT.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    BT.println(" m");

    BT.print("Humidity = ");
    BT.print(bme.readHumidity());
    BT.println(" %");

    BT.println();
}
