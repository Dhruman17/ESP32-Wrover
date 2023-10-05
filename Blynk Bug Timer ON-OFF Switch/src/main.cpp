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

// Variables for on and off times (in milliseconds)
unsigned long onTime = 5000; // Default on time is 5 seconds (5000 ms)

BlynkTimer timer;

// Variable to track LED state
bool ledOn = false;

// Function declarations
void toggleLED();
BLYNK_WRITE(V1);
BLYNK_WRITE(V2);

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
  digitalWrite(ledPin, LOW); // Ensure the LED is initially off

  // Attach timer function
  timer.setInterval(onTime, toggleLED);
}

void loop() {
  // Run Blynk
  Blynk.run();
  timer.run();
}

void toggleLED() {
  if (ledOn) {
    digitalWrite(ledPin, LOW);
    ledOn = false;
  } else {
    digitalWrite(ledPin, HIGH);
    ledOn = true;
  }
}

BLYNK_WRITE(V1) {
  // Toggle Button widget on V1 for turning ON the LED
  if (param.asInt() == 1) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    ledOn = true;
    timer.setInterval(onTime, toggleLED); // Set the timer for onTime (LED on)
  } else {
    // Ensure the LED is turned off
    digitalWrite(ledPin, LOW);
    ledOn = false;
    timer.disableAll(); // Disable all timers to prevent further LED toggling
  }
}

BLYNK_WRITE(V2) {
  // Toggle Button widget on V2 for turning OFF the LED
  if (param.asInt() == 1) {
    digitalWrite(ledPin, LOW); // Turn off the LED
    ledOn = false;
    timer.disableAll(); // Disable all timers to keep the LED off
  }
}
