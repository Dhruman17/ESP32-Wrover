#define BLYNK_TEMPLATE_ID "TMPL2IBmwwIRN"
#define BLYNK_TEMPLATE_NAME "Dhruman test"
#include <Arduino.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "BELL805";
char pass[] = "4E94D34AC4C6";
char auth[] = "ppqkclS7sdtb0YGk_nVDGX522o_7i4ed";

const int ledPin1 = 15; // GPIO15 for LED 1
const int ledPin2 = 2;  // GPIO2 for LED 2
const int ledPin3 = 5;  // GPIO5 for LED 3

#define LED1_VPIN V1
#define LED2_VPIN V2
#define LED3_VPIN V3
#define ON_TIME_SLIDER_VPIN V4
#define OFF_TIME_SLIDER_VPIN V5

bool ledState1 = false;
bool ledState2 = false;
bool ledState3 = false;

int onTime = 0;
int offTime = 0;

unsigned long prevTime = 0;
bool isOnTime = true;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
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

  digitalWrite(ledPin1, ledState1 && isOnTime);
  digitalWrite(ledPin2, ledState2 && isOnTime);
  digitalWrite(ledPin3, ledState3 && isOnTime);
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