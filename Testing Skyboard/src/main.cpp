#define BLYNK_TEMPLATE_ID "TMPL2IBmwwIRN"
#define BLYNK_TEMPLATE_NAME "Dhruman test"
#define BLYNK_AUTH_TOKEN "ppqkclS7sdtb0YGk_nVDGX522o_7i4ed"
#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include <driver/ledc.h>
#include "SkyBoardAlpha3.h"
#include <DHT.h>

#define DHTPIN 21
#define DHTTYPE DHT22 // Use DHT22, or DHT11, depending on your sensor type
DHT dht(DHTPIN, DHTTYPE); // Use IO21 (SDA) for the temperature sensor

bool ledState[8] = {false, false, false, false, false, false, false, false};
int atomizerOnTime = 0;
int atomizerOffTime = 0;
unsigned long prevTime = 0;
bool isOnTime = true;
int floatSensorStates[NUM_FLOAT_SWITCHES] = {0};

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  // Add this line for TEMP_SWITCH_VPIN setup
  pinMode(TEMP_SWITCH_VPIN, INPUT);

  for (int i = 0; i < NUM_FLOAT_SWITCHES; i++) {
    pinMode(FLOAT_SENSOR_PINS[i], (i < 6) ? INPUT_PULLUP : INPUT);
  }

  for (int i = 0; i < 8; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    // Configure LEDC channel for PWM
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
  Blynk.syncVirtual(TEMP_SWITCH_VPIN); // Sync the state of the Blynk switch
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

  // Check the Blynk switch state before sending temperature data
  Blynk.virtualWrite(V23, dht.readTemperature());
  Blynk.virtualWrite(V24, dht.readHumidity());

  delay(2000);
}

void readFloatData() {
  for (int i = 0; i < NUM_FLOAT_SWITCHES; i++) {
    floatSensorStates[i] = digitalRead(FLOAT_SENSOR_PINS[i]);
    Blynk.virtualWrite(FLOAT_SENSOR_VPINS[i], floatSensorStates[i]);
  }
}

// Attach Virtual Pins
BLYNK_WRITE_DEFAULT() {
  int pin = request.pin;
  if (pin == TEMP_SWITCH_VPIN) {
    // Handle the switch state
    int switchState = param.asInt();
    if (switchState == HIGH) {
       float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    Serial.print("Temp: ");
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
