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
unsigned long onTime = 50000; // Default on time is 90 seconds (90,000 ms)
unsigned long offTime = 4000;  // Default off time is 4 seconds (4,000 ms)

BlynkTimer timer;

// Variable to track LED state
bool ledOn = false;

// Variable to control timer execution
bool timerEnabled = true;

// Function declarations
void toggleLED();
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
  
  // Check if the timer should be disabled
  if (!timerEnabled) {
    timer.disableAll(); // Disable all timers
  }
}

BLYNK_WRITE(V2) {
  // Button widget on V2 to turn off the LED instantly
  if (param.asInt() == 1) {
    digitalWrite(ledPin, LOW);
    ledOn = false;
    timerEnabled = false; // Disable the timer execution
  }
}
