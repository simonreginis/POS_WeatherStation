#include <Wire.h>
#include <VirtualWire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define PAUSE 30000

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  vw_setup(2000);
  vw_set_tx_pin(4);
  
  Serial.println("Could not find a valid BME280 sensor, check wiring!");
    if (!bme.begin(0x76)) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
    }
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");


  char temp[16];
  dtostrf(bme.readTemperature(), 4, 1, temp);

  char most[7];
  dtostrf(bme.readHumidity(), 4, 1, most);

  char pres[7];
  dtostrf(bme.readPressure() / 100.0F, 6, 1, pres);

  strcat(temp, most);
  strcat(temp, pres);

  Serial.println(temp);
  digitalWrite(LED_BUILTIN, true); 
  vw_send((uint8_t *)temp, strlen(temp));
  vw_wait_tx(); 
  digitalWrite(LED_BUILTIN, false);

  Serial.println();
  delay(PAUSE);
}
