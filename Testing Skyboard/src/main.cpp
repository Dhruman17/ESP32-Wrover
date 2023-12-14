#define BLYNK_TEMPLATE_ID "TMPL23f8-CzzJ"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "RakzjAVWVXKlhJqbEzpj0daZgiYcq9I9"
#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include <driver/ledc.h>
#include "SkyBoardAlpha3.h"

#include <DHT.h>

#define DHTPIN 21
#define DHTTYPE DHT22 // Use DHT22, or DHT11, depending on your sensor type
DHT dht(DHTPIN, DHTTYPE); // Use IO21 (SDA) for the temperature sensor

#define TEMP_SWITCH_VPIN V22
int atomizerOnTime = 0;
int atomizerOffTime = 0;
unsigned long prevTime = 0;
bool isOnTime = true;
int floatSensorStates[numberOfFloatSensors] = {0};
unsigned long lastTemperatureSendTime = 0;
void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  // delay(1500);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  //You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
  for (int i = 0; i < numberOfFloatSensors; i++) {
    pinMode(floatSensorPins[i], (i < 6) ? INPUT_PULLUP : INPUT);
  }
  for (int i = 0; i < numberOfAtomizers; i++) {
    pinMode(atomizerPins[i], OUTPUT);
    // Configure LEDC channel for PWM
    ledcSetup(i, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(atomizerPins[i], i);
  }
}
void loop() {
   Blynk.run();
   Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(vPinAtomizerOnTime);
  Blynk.syncVirtual(vPinAtomizerOffTime);
  Blynk.syncVirtual(TEMP_SWITCH_VPIN);
  Blynk.syncVirtual(V23);
  Blynk.syncVirtual(V24);
  unsigned long currentTime = millis();

  if (isOnTime) {
    // Check if it's time to turn off the atomizers
    if (currentTime - prevTime >= atomizerOnTime * 1000) {
      isOnTime = !isOnTime;
      prevTime = currentTime;
    }
  } else {
    // Check if it's time to turn on the atomizers
    if (currentTime - prevTime >= atomizerOffTime * 1000) {
      isOnTime = !isOnTime;
      prevTime = currentTime;
    }
  }

  // Control atomizer LEDs based on the current state
  for (int i = 0; i < numberOfAtomizers; i++) {
    if (isOnTime) {
      if (atomizerState[i]) {
        ledcWrite(i,3 * PWM_MAX_DUTY_CYCLE/5);
      } else {
        ledcWrite(i, 0);
      }
    } else {
      ledcWrite(i, 0);  // Turn off all LEDs during off-time
    }
  }

  // You can include additional code here as needed

  delay(2000);
    float esp32Temperature = (temperatureRead() - 32) / 1.8; // Convert to Celsius
   Blynk.virtualWrite(V25, esp32Temperature);
Serial.print("ESP32 Temperature: ");
  Serial.print(esp32Temperature);
  Serial.println("°C");
  // Send temperature data every minute
  if (currentTime - lastTemperatureSendTime >= 60000) {
    float esp32Temperature = (temperatureRead() - 32) / 1.8; // Convert to Celsius
    Blynk.virtualWrite(V25, esp32Temperature); // Assuming V25 is the virtual pin for the Line Chart widget
    lastTemperatureSendTime = currentTime;
  Serial.print("ESP32 Temperature: ");
  Serial.print(esp32Temperature);
  Serial.println("°C");

  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}}
void readFloatData() {
  for (int i = 0; i < numberOfFloatSensors; i++) {
    floatSensorStates[i] = digitalRead(floatSensorPins[i]);
    Blynk.virtualWrite(vPinFloatSwitches[i], floatSensorStates[i]);
  }
}
// Attach Virtual Pins
BLYNK_WRITE_DEFAULT() {
  int pin = request.pin;
  // Check if it's handling the correct pin for the temperature switch
  if (pin == TEMP_SWITCH_VPIN) {
    // Handle the switch state
    int switchState = param.asInt();
    if (switchState == HIGH) {
      float temp = dht.readTemperature();
      float humidity = dht.readHumidity();
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.println("°C");
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println("%");
    }
  } else if (pin >= V1 && pin <= V10) {
    atomizerState[pin - V1] = (param.asInt() == 1);
  }
}

BLYNK_WRITE(V4) {
  atomizerOnTime = param.asInt();
}
BLYNK_WRITE(V5) {
  atomizerOffTime = param.asInt();
}