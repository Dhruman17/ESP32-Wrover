#define BLYNK_TEMPLATE_ID "TMPL2IBmwwIRN"
#define BLYNK_TEMPLATE_NAME "Dhruman test"
#define BLYNK_AUTH_TOKEN "ppqkclS7sdtb0YGk_nVDGX522o_7i4ed"
#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include <driver/ledc.h>
#include "Config.h"

bool ledState[8] = {false, false, false, false, false, false, false, false};
int atomizerOnTime = 0;
int atomizerOffTime = 0;
unsigned long prevTime = 0;
bool isOnTime = true;

int floatSensorStates[NUM_FLOAT_SWITCHES] = {0};

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  // delay(1500);  
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found

  //You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

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
  readFloatData();

  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(ON_TIME_SLIDER_VPIN);
  Blynk.syncVirtual(OFF_TIME_SLIDER_VPIN);
  // Blynk.syncAll();
  unsigned long currentTime = millis();

  if (isOnTime) { 
    if (currentTime - prevTime >= atomizerOnTime * 1000) { // if its been on for longer than the on time, then switch it off
      isOnTime = !isOnTime;
      prevTime = currentTime;
    }
  } else { 
    if (currentTime - prevTime >= atomizerOffTime * 1000) { // if its been off for longer than the off time, then switch
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
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
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
  if (pin >= V1 && pin <= V8) {
    ledState[pin - V1] = (param.asInt() == 1);
  }
}
BLYNK_WRITE(V4) {
  atomizerOnTime = param.asInt();
}
BLYNK_WRITE(V5) {
  atomizerOffTime = param.asInt();
}
