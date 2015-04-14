//////////////////////CONFIGURATION///////////////////////////////

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);

#define CHANNELS 9  //set the number of chanels in ppm
#define switch_number 2  //number of mode switches
#define TOTALSWITCHES 10 //trim Switches & additional switches
#define default_servo_value 1500  //set the default servo value
#define PPM_FrLen 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 300  //set the pulse length
#define onState 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define CHNUM 10 //Total number of internal channels storage array
////////////////////////PIN ASSIGN///////////////////////////////

#define SWAPin A14
#define SWBPin A15

#define LEDG 45
#define LEDR 44

#define BATT A0

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

//////////////////////////MENU////////////////////////////////////
#define KEY_NONE 0
#define KEY_PREV 1
#define KEY_NEXT 2
#define KEY_SELECT 3
#define KEY_INC 4
#define KEY_DEC 5
#define KEY_BACK 6

uint8_t uiKeyCodeFirst = KEY_NONE;
uint8_t uiKeyCodeSecond = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;

uint8_t menu_redraw_required = 0;
uint8_t last_key_code = KEY_NONE;


#define MAIN_MENU 6 //Max number of raws in Menu
#define SMI_1 4 //Number of Contents in SubMenu "MIX"

//////////////////////////MODE SW////////////////////////////////////
//ModeSW Positions
#define MODE_ONE 1
#define MODE_TWO 2
#define MODE_THREE 3

/////////////////////////ARRAYS///////////////////////////////////

// Ail Ele Thr Rud VRA VRB
int PIN[CHANNELS] = {Ail,Ele,Thr,Rud,VRA,VRB};

// Trim/additional Switch PIN Assignments (Need to maintain same order as PIN[] for trim switches)
int SwitchPIN[TOTALSWITCHES]={AilTR0, EleTR0, ThrTR0, RudTR0, AilTR1, EleTR1, ThrTR1, RudTR1, PUSHSW1, PUSHSW2};

String menu_strings[10];
String menu_Main[MAIN_MENU] = { "Mixer", "Ch Select","CH Reverse", "EP Adj", "Master Mode", "Settings"};
String menu_Sub1[SMI_1] = { "Mix 1", "Mix 2","Mix 3", "Mix 4"};
//String menu_strings3[CHANNELS]; // = { "CH 1 : ", "CH 2 : ","CH 3 : ", "CH 4 : ", "CH 5 : ", "CH 6 : "};
//String menu_strings4[CHANNELS] = { "CH 1 : ", "CH 2 : ","CH 3 : ", "CH 4 : ", "CH 5 : ", "CH 6 : "};
String channels[CHNUM] =             { "AIL", "ELE","THR", "RUD", "VRA", "VRB", "MIX1", "MIX2", "MIX3", "None"};

//////////////////////////////////////////////////////////////////

