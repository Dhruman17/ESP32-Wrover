#define BLYNK_TEMPLATE_ID "TMPL2IBmwwIRN"
#define BLYNK_TEMPLATE_NAME "Dhruman test"
#define BLYNK_AUTH_TOKEN "ppqkclS7sdtb0YGk_nVDGX522o_7i4ed"
#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include "Config.h" // Include the custom configuration header

bool ledState[8] = {false, false, false, false, false, false, false, false};
int onTime = 0;
int offTime = 0;
unsigned long prevTime = 0;
bool isOnTime = true;

void updateLEDs() {
  isOnTime = !isOnTime;
  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_PINS[i], ledState[i] && isOnTime);
  }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  for (int i = 0; i < 8; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
}
void loop() {
  Blynk.run();
  
Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);

  Blynk.syncVirtual(ON_TIME_SLIDER_VPIN);
  Blynk.syncVirtual(OFF_TIME_SLIDER_VPIN);
  unsigned long currentTime = millis();
   if (isOnTime) {
    if (currentTime - prevTime >= onTime * 1000) {
      isOnTime = !isOnTime;
      prevTime = currentTime;
    }
  } else {
    if (currentTime - prevTime >= offTime * 1000) {
   isOnTime = !isOnTime;      
   prevTime = currentTime;
    }
  }
  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_PINS[i], ledState[i] && isOnTime);
  }
  // Update LEDs
}

BLYNK_WRITE(V1) { ledState[0] = (param.asInt() == 1); }
BLYNK_WRITE(V2) { ledState[1] = (param.asInt() == 1); }
BLYNK_WRITE(V3) { ledState[2] = (param.asInt() == 1); }
BLYNK_WRITE(V6) { ledState[5] = (param.asInt() == 1); }
BLYNK_WRITE(V7) { ledState[6] = (param.asInt() == 1); }
BLYNK_WRITE(V8) { ledState[7] = (param.asInt() == 1); }

BLYNK_WRITE(V4) { onTime = param.asInt(); }
BLYNK_WRITE(V5) { offTime = param.asInt(); }