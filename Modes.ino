int ModeTemp,ModeTemp1;
int KeyActive;
void CheckcMode() {
  if ((PUSHSWA) && (PUSHSWB))
  {
    if (KeyActive) {
      Mode++;
      KeyActive = 0;
    }
    if (Mode == 1) {
      menu_redraw_required = 1;
      MENU_ITEMS = MAIN_MENU;
      for (int i = 0; i <  MENU_ITEMS; i++) menu_strings[i] = menu_Main[i];
    }
    else if (Mode > 1)
    {
      Mode = 0;
    }
    // Serial.println("Mode: " + String(Mode));
  }
  switch (Mode) {
    case 0:
      if (!PUSHSWA && PUSHSWB)
      {
        if (KeyActive) {
          ModeTemp1++;
          KeyActive = 0;
        }
        if (ModeTemp1 > 1) ModeTemp1 = 0;
      }
      if (!ModeTemp1)
      {
        Screen();
        Trim();
        UPDATEPPM = 1;
      }
      else
      {
        ScreenPPM();
        Trim();
        UPDATEPPM = 1;
      }
      break;
    case 1:
      if (PUSHSWA && !PUSHSWB)
      {
        if (KeyActive) {
          ModeTemp++;
          KeyActive = 0;
        }
        if (ModeTemp > 1) ModeTemp = 0;
      }
      if (!ModeTemp)
      {
        UPDATEPPM = 0;
        menu_redraw_required = 1;
        Menu();
        //KeyActive = 0;
      }
      else
      {
        UPDATEPPM = 1;
        Screen();
        //KeyActive = 0;
      }
      break;
  }
};


void CheckCalibMode() {
  if (!digitalRead(PUSHSW1) && !digitalRead(PUSHSW2) && analogRead(SWAPin) < 250 && analogRead(SWBPin) > 750)
  {
    {
      for (int i = 0; i < (CHANNELS - 2); i++) {
        StickMin[i] = StickMid[i] = StickMax[i] = 0;
      }
    };
    while (analogRead(SWAPin) < 250 && analogRead(SWBPin) > 750)
    {
      CalibVals();
      for (int i = 0; i < (CHANNELS); i++) {
        if (AnalogRead(PIN[i]) > StickMax[i]) {
          StickMax[i] = AnalogRead(PIN[i]);
        }
        if (AnalogRead(PIN[i]) < StickMin[i]) {
          StickMin[i] = AnalogRead(PIN[i]);
        }
      }
    };
    for (int i = 0; i < (CHANNELS); i++) {
      StickMid[i] = AnalogRead(PIN[i]);
    }
    setData();
  };
};

