//Include the library files
#define BLYNK_TEMPLATE_ID "TMPL2IBmwwIRN"
#define BLYNK_TEMPLATE_NAME "Dhruman test"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Enter your Auth token
char auth[] = "xW0zDUCZP-yB9y1Hr9wdABB_VLc4czRs";

//Enter your WIFI SSID and password
char ssid[] = "BELL805";
char pass[] = "4E94D34AC4C6";

void setup(){
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop(){
  Blynk.run();
}