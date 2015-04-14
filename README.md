# SuperTX

Currently working with FLYSKY CT6B + arduino Mega + SSD1306 Based IIC / I2C OLED (128x64 Pixels)

Done:
Now trim works through software(actual ct6b can only trimmed mechanically before) in other radios .
End points can be adjust through menu.
Can assign any channel to any stick via menu.
Can reverse channels via menu.
Can change up to 6 flight modes for APM (2x3position switches)
Up to 9 channel works corresponding rx (before it was a 6 channel radio).
Added calibration mode (all sticks end points and center point will calibrate to min 1000 , mid 1500 and max 2000)
Works fine with 2S - 3S LiPo (6V- 13V)


Pin Assignments Below

#define SWAPin A14
#define SWBPin A15

#define LEDG 45
#define LEDR 44

#define BATT A0 // Please dont try to connect directly to battery, Need Voltage Divider To Connect Battery.

//Analog pins without Prefix "A"
#define Ail 8
#define Ele 9
#define Thr 10
#define Rud 11
#define VRA 12
#define VRB 13

// Push Switches For Menu/additional operations
#define PUSHSW1  32
#define PUSHSW2  33

//PPM Output Pin to TX Module
#define PPMPin 2

// Digital Pins Trim Switches
#define EleTR0  5
#define EleTR1  6
#define AilTR0  7
#define AilTR1  8
#define ThrTR0  9
#define ThrTR1  10
#define RudTR0  11
#define RudTR1  12
