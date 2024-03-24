#include<Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Defines
#define THRESHOLD 60

// Defined pins
const int encendido = T6; // GPIO33, touch sensor, on/off button
const int thermoBus = GPIO_NUM_25; // GPIO36(UP), temperature bus

// Usage of thermometer buses
OneWire oneWire(thermoBus);
DallasTemperature sensors (&oneWire);

// Variables
int cont = 0;
float temperatureC;

// Interruptions
// Capacitor sensor wake up. Use of ISRAM memory, faster than FLASH
void IRAM_ATTR touchSensorWakeUp(){
    Serial.println(cont);
    cont++;
}

void setup() 
{
    Serial.begin(115200);
    sensors.begin();
    delay(1000);
    // Disbaling all options except WIFI and touchpad
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    esp_sleep_enable_wifi_wakeup();
    esp_sleep_enable_touchpad_wakeup();

    // Use a threshold for the pin to wake up
    // the function is used as an interruption to use it to do the first things we use
    touchAttachInterrupt(encendido,touchSensorWakeUp,THRESHOLD);
}
 
void loop() {
  esp_light_sleep_start();
  // Ask thermometer for temperature, save it and print it
  sensors.requestTemperatures();
  temperatureC = sensors.getTempCByIndex(0);
  Serial.println(temperatureC);
  delay(3000);
}