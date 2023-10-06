#define BLYNK_TEMPLATE_ID "TMPL2IBmwwIRN"
#define BLYNK_TEMPLATE_NAME "Dhruman test"
#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "BELL805";
char pass[] = "4E94D34AC4C6";
char auth[] = "ppqkclS7sdtb0YGk_nVDGX522o_7i4ed";

// LED connected to this GPIO pin
const int ledPin = 2;  // Change this to match your board's LED pin

// Virtual Pin assignments
int onTimePin = V0;
int offTimePin = V1;
int togglePin = V2;

// Flags for circuit control
bool circuitOn = true;

BLYNK_WRITE(togglePin) {
  int buttonState = param.asInt(); // Read the button state (0 or 1)
  if (buttonState == 1) {
    // Button is pressed (turned off)
    circuitOn = false;
  } else {
    // Button is released (turned on)
    circuitOn = true;
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Implement your logic here to control the circuit based on on-time and off-time
  if (circuitOn) {
    // Do something when the circuit is on
  } else {
    // Turn off the circuit completely
    digitalWrite(ledPin, LOW);
  }
}
