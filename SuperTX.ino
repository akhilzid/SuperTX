#include <EEPROM.h>
#include "U8glib.h"
#include "Config.h"
#include "Variables.h"

void setup() {
  FSmsg(0, 40, "Initializing....");
  //SaveDefault();
  Serial.begin(9600);
  pinMode(PPMPin, OUTPUT);
  digitalWrite(PPMPin, !onState);  //set the PPM signal pin to the default state (off)
  for (int i = 0; i < TOTALSWITCHES; i++) pinMode(SwitchPIN[i], INPUT_PULLUP);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDR, OUTPUT);
  digitalWrite(LEDR, HIGH);
  getData();
  setTimer();
  CheckCalibMode();
  StickVal[6] = 1000;
  for (int thisReading = 0; thisReading < numReadings; thisReading++){
    float v = (float)analogRead(BATT)* 5.0 / (float)VoltageDiv;
    readings[thisReading] = v;
    total +=v;
  }
  ADCSRA &= ~PS_128;  // remove bits set by Arduino library
  ADCSRA |= PS_16;    // set prescaler
  
  FSmsg(45, 40, "Done");
}

void loop() {
  StickCalc();
  LCOUNT++;
  NewTime = millis();
  if (NewTime - PrevTime >= GapTime) {
    PrevTime = NewTime;
    LTIME = ((float)LCOUNT * (float)1000) / (float)GapTime; //Number Of Loops Per Second
    LCOUNT = 0;
    Batt();
    SWPos();
    Switch();
    SwitchCalc();
    CheckcMode();
  }

  if (UPDATEPPM) {
    for (int i = 0; i < CHANNELS; i++) 
    {
     if (CH[i] == 0 || CH[i] == 1 || CH[i] == 3) //For channels Ail, Ele, Rud
     {
       int ppm_ep = (StickVal[CH[i]] <= 0)? CH_EMIN[CH[i]] : CH_EMAX[CH[i]];
        int ppm_temp = map(StickVal[CH[i]], ppm_ep , 0 , ppm_ep , StickTRIM[CH[i]]);
      
        ppm[i] = 1500 + ((CH_Reversed[i] == 0)? (+ppm_temp): (-ppm_temp));
      }
      else                                      //For all other linear channels like throttle and VR
      { 
        ppm[i] = 1500 + ((CH_Reversed[i] == 0)? (+StickVal[CH[i]]): (-StickVal[CH[i]]));
      }
    }
  }
}

int AnalogRead(int val)
{
return (analogRead(val) - 511);
}
