#include <Arduino.h>
#include <SkyBoardAlpha3.h>
/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2PXtDr4Wr"
#define BLYNK_TEMPLATE_NAME "Typical Skyboard Template"
#define BLYNK_AUTH_TOKEN "pNRYIC9oN-V9KKfwGnfOQiEHnyQusPBg"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
// WiFi
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Guest";
char pass[] = "Airbnb73";
BlynkTimer timer;
BlynkTimer timer2;
// Pins
int atomizerAddress[numberOfAtomizers] = atomizerPins;
int floatSensorAddress[numberOfFloatSwitches] = floatSensorPins;
int atomizerVirtualAddress[numberOfAtomizers] = vPinAtomizers;
int floatSensorVirtualAddress[numberOfFloatSwitches] = vPinFloatSwitches;
// States
int atomizerEnable[numberOfAtomizers] = {0}; // Create array of atomizer states set to 0
int atomizerState = 0;
int floatSensorStates[numberOfFloatSwitches] = {0};
// Atomizer Timing
int atomizerOnTime = 0;
int atomizerOffTime = 0;
unsigned long onTimeStartTime = 0;
unsigned long offTimeStartTime = 0;
bool isOnTime = true;
// This function is called every time the device is connected to the Blynk.Cloud
// Attach Virtual Pins
BLYNK_WRITE(vPinAtomizerOnTime) {
  atomizerOnTime = param.asInt();
}
BLYNK_WRITE(vPinAtomizerOffTime) {
  atomizerOffTime = param.asInt();
}
BLYNK_WRITE_DEFAULT() {
  int pin = request.pin;
  atomizerEnable[pin - vPinAtomizersStartingIndex] = param.asInt();
  onTimeStartTime += atomizerOnTime;
}
void atomizersSwitch() {
  unsigned long currentTime = millis();
  // Check if it's on-time and if it's time to switch off
  if (isOnTime) {
    if (atomizerOnTime > 0 && (currentTime - onTimeStartTime >= atomizerOnTime * 1000)) {
      // Turn off atomizers
      for (int i = 0; i < numberOfAtomizers; i++) {
        ledcWrite(i, 0);
      }
      isOnTime = false;
      offTimeStartTime = currentTime;
    }
  }
  // Check if it's off-time and if it's time to switch on
  else {
    if (atomizerOffTime > 0 && (currentTime - offTimeStartTime >= atomizerOffTime * 1000)) {
      // Turn on atomizers for enabled ones
      for (int i = 0; i < numberOfAtomizers; i++) {
        if (atomizerEnable[i] == 1) {
          ledcWrite(i, 3 * pwmMaxDutyCycle / 5);
        }
      }
      isOnTime = true;
      onTimeStartTime = currentTime;
    }
  }
}
void readFloatData() {
  for (int i = 0; i < numberOfFloatSwitches; i++) {
    floatSensorStates[i] = digitalRead(floatSensorAddress[i]);
    Blynk.virtualWrite(floatSensorVirtualAddress[i], floatSensorStates[i]);
  }
}
void setup() {
  // Debug console
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  for (int i = 0; i < 6; i++) {
    pinMode(floatSensorAddress[i], INPUT_PULLUP);
  }
  for (int j = 6; j < numberOfFloatSwitches; j++) {
    pinMode(floatSensorAddress[j], INPUT);
  }
  for (int i = 0; i < numberOfAtomizers; i++) {
    ledcSetup(i, pwmF, pwmResolution);
    ledcAttachPin(atomizerAddress[i], i);
  }
  timer.setInterval(1000L, atomizersSwitch);
  timer.setInterval(1000L, readFloatData);
  Blynk.syncAll();
}
void loop() {
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}