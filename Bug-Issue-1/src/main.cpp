#define BLYNK_TEMPLATE_ID "TMPL2IBmwwIRN"
#define BLYNK_TEMPLATE_NAME "Dhruman test"
#define BLYNK_AUTH_TOKEN "ppqkclS7sdtb0YGk_nVDGX522o_7i4ed"

#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include "Config.h" // Include the custom configuration header
// Blynk settings

bool ledState1 = false;
bool ledState2 = false;
bool ledState3 = false;

int onTime = 0;
int offTime = 0;

unsigned long prevTime = 0;
bool isOnTime = true;

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
}

void loop() {
  Blynk.run();

  // Use Blynk.syncVirtual to check the state of the LED switches and timers
  Blynk.syncVirtual(LED1_VPIN);
  Blynk.syncVirtual(LED2_VPIN);
  Blynk.syncVirtual(LED3_VPIN);
  Blynk.syncVirtual(ON_TIME_SLIDER_VPIN);
  Blynk.syncVirtual(OFF_TIME_SLIDER_VPIN);

  // Update LEDs
  unsigned long currentTime = millis();

  if (isOnTime) {
    if (currentTime - prevTime >= onTime * 1000) {
      isOnTime = false;
      prevTime = currentTime;
    }
  } else {
    if (currentTime - prevTime >= offTime * 1000) {
      isOnTime = true;
      prevTime = currentTime;
    }
  }

  digitalWrite(LED_PIN_1, ledState1 && isOnTime);
  digitalWrite(LED_PIN_2, ledState2 && isOnTime);
  digitalWrite(LED_PIN_3, ledState3 && isOnTime);
}

BLYNK_WRITE(LED1_VPIN) {
  int value = param.asInt();
  ledState1 = (value == 1);
}

BLYNK_WRITE(LED2_VPIN) {
  int value = param.asInt();
  ledState2 = (value == 1);
}

BLYNK_WRITE(LED3_VPIN) {
  int value = param.asInt();
  ledState3 = (value == 1);
}

BLYNK_WRITE(ON_TIME_SLIDER_VPIN) {
  onTime = param.asInt();
}

BLYNK_WRITE(OFF_TIME_SLIDER_VPIN) {
  offTime = param.asInt();
}
