#include <Arduino.h>
#define numberOfAtomizers 8
#define atomizerPins {4,5,2,14,15,17,16,19}
#define vPinAtomizerOnTime V0
#define vPinAtomizerOffTime V1
#define vPinAtomizersStartingIndex V2
#define vPinAtomizers {V2, V3, V4, V5, V6, V7,V8,V9}
#define numberOfFloatSwitches 10
#define floatSensorPins {23,25,26,27,32,33,34,35,36,39}
#define vPinFloatSwitchStartingIndex V12
#define vPinFloatSwitches {V12, V13, V14, V15, V16, V17, V18, V19, V20, V21}
#define pwmF 108000
#define pwmResolution 4
#define pwmMaxDutyCycle 15

// IMP!!! Please set number of atomizers, sensors, atomizer pins, sensor pins, and vPinAtomizers,VPinSwitches according to use case
// 4,5,2,14,15,17,16,19 -> Atomizer pins
// 23,25,26,27,32,33,34,35,36,39 -> Sensor Pins 
// A1=4, A2=5, A3=2, A4=14, A5=15, A6=17, A7=16, A8=19
// S1=23, S2=25, S3=26, S4=27, S5=32, S6=33, S7=34, S8=35, S9=36, S10=39