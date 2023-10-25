#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
#define WIFI_SSID "BELL805"
#define WIFI_PASS "4E94D34AC4C6"

// Pins for LEDs
const int LED_PINS[] = {15, 2, 5, 4, 14, 17, 16, 19};

// Virtual pins for Blynk
const int LED_VPINS[] = {V1, V2, V3, V6, V7, V8, V9, V10};
const int ON_TIME_SLIDER_VPIN = V4;
const int OFF_TIME_SLIDER_VPIN = V5;

#endif // CONFIG_H
