#ifndef CONFIG_H
#define CONFIG_H
// WiFi credentials
#define WIFI_SSID "BELL805"
#define WIFI_PASS "MceWan@444"

#define numberOfAtomizers 8
// Pins for LEDs
const int atomizerPins[] = {15, 2, 5, 4, 14, 17, 16, 19};
// const int atomizerPins[] = {23,19,18,25,17,16,04,2};
// Virtual pins for Blynk
const int vPinAtomizerOnTime = V4;
const int vPinAtomizerOffTime = V5;
const int vPinAtomizers[] = {V1, V2, V3, V6, V7, V8, V9, V10};
bool atomizerState[8] = {false, false, false, false, false, false, false, false};
// LEDC PWM Configuration
#define PWM_FREQUENCY 108000
#define PWM_RESOLUTION 4
#define PWM_MAX_DUTY_CYCLE 15
// Float Switches
#define numberOfFloatSensors 10
const int floatSensorPins[] = {23,25,26,27,32,33,34,35,36,39};
// const int floatSensorPins[] = {23,27,26,25,33,32,35,34,36,39};
const int vPinFloatSwitchStartingIndex = V12;
const int vPinFloatSwitches[] = {V12, V13, V14, V15, V16, V17, V18, V19, V20, V21};
#endif // CONFIG_H
//The above configuration are as per Dhruman's Board.
// IMP!!! Please set number of atomizers, sensors, atomizer pins, sensor pins, and vPinAtomizers,VPinSwitches according to use case

// For Board JST V3 onwards
// 4,5,2,14,15,17,16,19 -> Atomizer pins
// 23,25,26,27,32,33,34,35,36,39 -> Sensor Pins
// A1=4, A2=5, A3=2, A4=14, A5=15, A6=17, A7=16, A8=19
// S1=23, S2=25, S3=26, S4=27, S5=32, S6=33, S7=34, S8=35, S9=36, S10=39
// const int atomizerPins[] = {4,5,2,14,15,17,16,19};
// const int floatSensorPins[] = {23,25,26,27,32,33,34,35,36,39};


// For Board JST V2.1
// const int atomizerPins[] = {23,19,18,25,17,16,04,2};
// const int floatSensorPins[] = {23,27,26,25,33,32,35,34,36,39};