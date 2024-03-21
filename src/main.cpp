#include<Arduino.h>

#define THRESHOLD 50

int cont = 0;

// Use of ISRAM memory, faster than FLASH
void IRAM_ATTR touchSensorWakeUp(){
    Serial.println(cont);
    cont++;
}

void setup() 
{
    Serial.begin(115200);
    // Monitor Serie use
    delay(1000);
    // Disbaling all options except WIFI and touchpad
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    esp_sleep_enable_wifi_wakeup();
    esp_sleep_enable_touchpad_wakeup();

    // Use a threshold for the pin to wake up
    // the function is used as an interruption to use it to do the first things we use
    touchAttachInterrupt(T9,touchSensorWakeUp,THRESHOLD);
}
 
void loop() {
  esp_light_sleep_start();
}