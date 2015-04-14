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
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;
  FSmsg(45, 40, "Done");
}

void loop() {
  SWPos();
  StickCalc();
  Switch();
  SwitchCalc();
  NewTime1 = millis();
  if (NewTime1 - PrevTime1 >= 400UL) {
    PrevTime1 = NewTime1;
    Batt();
  }
  LCOUNT++;
  NewTime = millis();
  if (NewTime - PrevTime >= GapTime) {
    PrevTime = NewTime;
    LTIME = ((float)LCOUNT * (float)1000) / (float)GapTime;
    LCOUNT = 0;
    CheckcMode();
  }

  if (UPDATEPPM) {
    for (int i = 0; i < CHANNELS; i++) {

      if (CH[i] == 0 || CH[i] == 1 || CH[i] == 3) {
        if (StickVal[CH[i]] < 500)
        {
          if (CH_Reversed[i] == 0) ppm[i] = 1000 + map(StickVal[CH[i]], CH_EMIN[CH[i]], 500  , CH_EMIN[CH[i]],StickTRIM[CH[i]]);
          else ppm[i] = 2000 - map(StickVal[CH[i]], CH_EMIN[CH[i]], 500  , CH_EMIN[CH[i]],StickTRIM[CH[i]]);
        }
        else if (StickVal[CH[i]] > 500)
        {
          if (CH_Reversed[i] == 0) ppm[i] = 1000 + map(StickVal[CH[i]], 500,  CH_EMAX[CH[i]], StickTRIM[CH[i]], CH_EMAX[CH[i]]);
          else ppm[i] = 2000 - map(StickVal[CH[i]], 500,  CH_EMAX[CH[i]], StickTRIM[CH[i]], CH_EMAX[CH[i]]);
        }
        else  ppm[i] = 1000 + StickTRIM[CH[i]];
      }
      else
      { if (CH_Reversed[i] == 0) ppm[i] = 1000 + StickVal[CH[i]];
        else ppm[i] = 2000 - StickVal[CH[i]];
      }
    }
  }
}
