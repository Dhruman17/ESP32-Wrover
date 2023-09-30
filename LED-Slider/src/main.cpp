#define BLYNK_TEMPLATE_ID "TMPL2IBmwwIRN"
#define BLYNK_TEMPLATE_NAME "Dhruman test"
#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "BELL805";
char pass[] = "4E94D34AC4C6";

// Blynk Auth Token
char auth[] = "ppqkclS7sdtb0YGk_nVDGX522o_7i4ed";

// LED connected to this GPIO pin
const int ledPin = 2;  // Change this to the GPIO pin you've connected your LED to

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
}

// Function to update LED brightness when the Slider value changes
BLYNK_WRITE(V0) {
  int sliderValue = param.asInt(); // Get slider value (0-1023)
  int brightness = map(sliderValue, 0, 255, 0, 255); // Map to LED brightness (0-255)
  analogWrite(ledPin, brightness); // Set LED brightness
}
