//////////////////////////MENU////////////////////////////////////
int menu_current = 0;
int submenu_current = 0;
int MENU_ITEMS;

//////////////////////////MODE////////////////////////////////////
int Mode = 0;

//////////////////////////PPM////////////////////////////////////
int ppm[CHANNELS];
int UPDATEPPM = 1;

//////////////////////////STICKS////////////////////////////////////
int StickVal[CHNUM + 1];
//int StickVal[CHANNELS + 1];
int StickMin[CHANNELS], StickMid[CHANNELS], StickMax[CHANNELS], StickTRIM[CHANNELS];
int Deadband; // Deadband for AIL/ELE/RUD
//////////////////////////SWITCHES////////////////////////////////////
int SWA, SWB;
int PUSHSWA, PUSHSWB;
int SwitchPrev[TOTALSWITCHES];

//////////////////////////VOLTAGE READING////////////////////////////////////
const int numReadings = 50;
float readings[numReadings];      // the readings from the analog input
int readIndex = 0;                // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average
int VoltageDiv;                // 511.5

//////////////////////////CHANNELS////////////////////////////////////
int CH[CHANNELS];
int CH_Reversed[CHANNELS];
int CH_EMIN[CHANNELS], CH_EMAX[CHANNELS];

//////////////////////////GENERAL////////////////////////////////////
int LCOUNT;
int LTIME;
int GapTime = 50;
int SingleStep = true;
unsigned long NewTime, PrevTime, NewTime1, PrevTime1, NewTime2, PrevTime2;
