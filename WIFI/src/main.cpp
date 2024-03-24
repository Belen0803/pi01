#include<Arduino.h>
#include <HardwareSerial.h>

//Defines


// Defined pins

// Usage of UART buses
// Using UART1 instead of 2 because it cant wake up from UART2, using same pins as UART2
// This may cause some problems in the future
HardwareSerial SerialPort(1);

// Variables
int cont = 0;

// Interruptions


void setup() 
{
    Serial.begin(115200);
    // 9600 bauds will be enough (I think)
    SerialPort.begin(9600, SERIAL_8N1, 16, 17);
    delay(1000);
    // Disbaling all options except WIFI and touchpad
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    esp_sleep_enable_wifi_wakeup();
    esp_sleep_enable_uart_wakeup(1);

    // Use a threshold for the pin to wake up
    // the function is used as an interruption to use it to do the first things we use
}
 
void loop() {
  esp_light_sleep_start();
  
  // Ask thermometer for temperature, save it and print it
  delay(3000);
}