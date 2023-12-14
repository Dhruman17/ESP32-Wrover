#define BLYNK_TEMPLATE_ID "TMPL23f8-CzzJ"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "RakzjAVWVXKlhJqbEzpj0daZgiYcq9I9"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <config.h>

int blinkFrequency = 1000; // Default frequency in milliseconds
int brightness = 100;      // Default brightness (0-255)
char ssid[] = "BELL805";
char pass[] = "MceWan@444";

int ledPins[] = {2, 5, 15};
int numLeds = 3;

BlynkTimer timer;

void blinkLed();

BLYNK_WRITE(V31) {
  // Get the slider value and update the blinkFrequency
  blinkFrequency = param.asFloat();

  // Convert Hertz to milliseconds
  int interval = (int)(1000.0 / blinkFrequency);

  // Update the interval of the timer based on the new blinkFrequency
  timer.setInterval(interval, blinkLed);
  
  // Notify Blynk about the current frequency
  Blynk.virtualWrite(V31, blinkFrequency);
}

BLYNK_WRITE(V32) {
  // Get the brightness value from the Number Input widget (1-100)
  brightness = param.asInt();

  // Notify Blynk about the current brightness
  Blynk.virtualWrite(V32, brightness);
}
void setup() {
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Initial conversion from Hertz to milliseconds
  int interval = (int)(1000.0 / blinkFrequency);
  timer.setInterval(interval, blinkLed);
}

void loop() {
  Blynk.run();
  timer.run();
  Blynk.syncVirtual(V31);
    Blynk.syncVirtual(V32);
}


void blinkLed() {
  for (int i = 0; i < numLeds; i++) {
    // Toggle the LED state
    digitalWrite(ledPins[i], !digitalRead(ledPins[i]));

    // Set the LED brightness
    analogWrite(ledPins[i], brightness * 2.55); // Map 1-100 to 0-255
  }
}
