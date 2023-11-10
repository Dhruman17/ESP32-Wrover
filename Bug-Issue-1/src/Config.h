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

// LEDC PWM Configuration
#define PWM_FREQUENCY 108000
#define PWM_RESOLUTION 4
#define PWM_MAX_DUTY_CYCLE 15

// Float Switches
#define NUM_FLOAT_SWITCHES 10
const int FLOAT_SENSOR_PINS[] = {23, 25, 26, 27, 32, 33, 34, 35, 36, 39};
const int FLOAT_SENSOR_VPINS_START = V12;
const int FLOAT_SENSOR_VPINS[] = {V12, V13, V14, V15, V16, V17, V18, V19, V20, V21};

#endif // CONFIG_H
//The above configuration are as per Dhruman's Board.

// IMP!!! Please set number of atomizers, sensors, atomizer pins, sensor pins, and vPinAtomizers,VPinSwitches according to use case
// 4,5,2,14,15,17,16,19 -> Atomizer pins
// 23,25,26,27,32,33,34,35,36,39 -> Sensor Pins 
// A1=4, A2=5, A3=2, A4=14, A5=15, A6=17, A7=16, A8=19
// S1=23, S2=25, S3=26, S4=27, S5=32, S6=33, S7=34, S8=35, S9=36, S10=39