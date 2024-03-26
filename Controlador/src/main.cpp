#include<Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HardwareSerial.h>

//Defines
#define THRESHOLD 60
#define APAGADO 100

// Defined pins
const int encendido = T6; // GPIO33, touch sensor, on/off button
const int thermoBus = GPIO_NUM_25; // GPIO36(UP), temperature bus

// Usage of thermometer buses
OneWire oneWire(thermoBus);
DallasTemperature sensors (&oneWire);

// Usage of UART buses
// Using UART2 for comodity
HardwareSerial SerialPort(2);

// Variables
int cont = 0;
float tempM;
int bebida, water, sugar, tank1, tank2,tank3,tank4,tempI;
bool botonApagar = 0;

// Interruptions
// Capacitor sensor wake up. Use of ISRAM memory, faster than FLASH
void IRAM_ATTR touchSensorWakeUp(){
    SerialPort.print(APAGADO);
    botonApagar = 1;
}

void setup() 
{
    Serial.begin(115200);
    SerialPort.begin(9600, SERIAL_8N1, 16, 17);
    sensors.begin();
    delay(1000);
    // Disbaling all options except WIFI and touchpad
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    esp_sleep_enable_touchpad_wakeup();

    // Use a threshold for the pin to wake up
    // the function is used as an interruption to use it to do the first things we use
    touchAttachInterrupt(encendido,touchSensorWakeUp,THRESHOLD);
}
 
void loop() {
  esp_light_sleep_start();
  // Ask thermometer for temperature, save it and print it
  /*sensors.requestTemperatures();
  tempM = sensors.getTempCByIndex(0);
  Serial.println(tempM);*/

  // There will be only one comunicattion, each number will correspond to one characteristic
  // of the drink, except for temperature, will be 2 digits for it
  if (SerialPort.available()){
    bebida = SerialPort.read();
    SerialPort.print(200);

    // We get every number and its corresponding value
    // 1º number -> Sugar
    sugar = bebida % 10;
    bebida = bebida / 10;
    // 2º number -> Water
    water = bebida % 10;
    bebida = bebida / 10;
    // 3º number -> Tank 1
    tank1 = bebida % 10;
    bebida = bebida / 10;
    // 4º number -> Tank 2
    tank2 = bebida % 10;
    bebida = bebida / 10;
    // 5º number -> Tank 3
    tank3 = bebida % 10;
    bebida = bebida / 10;
    // 6º number -> Tank 4
    tank4 = bebida % 10;
    bebida = bebida / 10;
    // 7º & 8º number -> Temperature
    tempI = bebida;
  }




  // Information will be transmited from esp WIFI each number will be referred to each tank
  // There will be an exception in case the turn off button is pressed so the variable will be saved
  
  delay(3000);
}