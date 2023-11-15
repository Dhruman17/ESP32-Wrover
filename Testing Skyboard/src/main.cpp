#define BLYNK_TEMPLATE_ID "TMPL23f8-CzzJ"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "RakzjAVWVXKlhJqbEzpj0daZgiYcq9I9"
#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include "SkyBoardAlpha3.h"
#include <DHT.h>

#define DHTPIN 21
#define DHTTYPE DHT22 // Use DHT22, or DHT11, depending on your sensor type
DHT dht(DHTPIN, DHTTYPE); // Use IO21 (SDA) for the temperature sensor

#define TEMP_SWITCH_VPIN V22
bool ledState[8] = {false, false, false, false, false, false, false, false};
int atomizerOnTime = 0;
int atomizerOffTime = 0;
unsigned long prevTime = 0;
bool isOnTime = true;
int floatSensorStates[NUM_FLOAT_SWITCHES] = {0};
unsigned long lastTemperatureSendTime = 0;

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  pinMode(TEMP_SWITCH_VPIN, INPUT);

  for (int i = 0; i < NUM_FLOAT_SWITCHES; i++) {
    pinMode(FLOAT_SENSOR_PINS[i], (i < 6) ? INPUT_PULLUP : INPUT);
  }

  for (int i = 0; i < 8; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    ledcSetup(i, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(LED_PINS[i], i);
  }
}

void loop() {
  Blynk.run();
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(ON_TIME_SLIDER_VPIN);
  Blynk.syncVirtual(OFF_TIME_SLIDER_VPIN);
  Blynk.syncVirtual(TEMP_SWITCH_VPIN);
  Blynk.syncVirtual(V23);
  Blynk.syncVirtual(V24);

  unsigned long currentTime = millis();

  if (isOnTime) {
    if (currentTime - prevTime >= atomizerOnTime * 1000) {
      isOnTime = !isOnTime;
      prevTime = currentTime;
    }
  } else {
    if (currentTime - prevTime >= atomizerOffTime * 1000) {
      isOnTime = !isOnTime;
      prevTime = currentTime;
    }
  }

  for (int i = 0; i < 8; i++) {
    if (ledState[i] && isOnTime) {
      ledcWrite(i, PWM_MAX_DUTY_CYCLE);
    } else {
      ledcWrite(i, 0);
    }
  }
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

  }

  delay(2000);
}

void readFloatData() {
  for (int i = 0; i < NUM_FLOAT_SWITCHES; i++) {
    floatSensorStates[i] = digitalRead(FLOAT_SENSOR_PINS[i]);
    Blynk.virtualWrite(FLOAT_SENSOR_VPINS[i], floatSensorStates[i]);
  }
}

BLYNK_WRITE_DEFAULT() {
  int pin = request.pin;
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
  } else if (pin >= V1 && pin <= V8) {
    ledState[pin - V1] = (param.asInt() == 1);
  }
}

BLYNK_WRITE(V4) {
  atomizerOnTime = param.asInt();
}

BLYNK_WRITE(V5) {
  atomizerOffTime = param.asInt();
}
