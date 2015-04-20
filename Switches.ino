void Switch() {
  for (int i = 0; i < TOTALSWITCHES; i++) {
    if (!digitalRead(SwitchPIN[i]) && !SwitchPrev[i]) {
      SwitchPrev[i] = 1;
      KeyEvent(SwitchPIN[i], true);
    } else if (digitalRead(SwitchPIN[i]) && SwitchPrev[i]) {
      SwitchPrev[i] = 0;
      KeyEvent(SwitchPIN[i], false);
    };
  }
}
int Pause;
void SWStep(void) {
  uiKeyCodeSecond = uiKeyCodeFirst;
  if ( StickVal[1] > 100 )
    uiKeyCodeFirst = KEY_PREV;
  else if ( StickVal[1] < -100 )
    uiKeyCodeFirst = KEY_NEXT;
  else if (StickVal[0] > 100 )
    uiKeyCodeFirst = KEY_SELECT;
  else if (StickVal[0] < -100 )
    uiKeyCodeFirst = KEY_BACK;
  else if (StickVal[3] > 100 )
    uiKeyCodeFirst = KEY_INC;
  else if (StickVal[3] < -100 )
    uiKeyCodeFirst = KEY_DEC;
  else
    uiKeyCodeFirst = KEY_NONE;

  if (uiKeyCodeSecond == uiKeyCodeFirst )
  {
    if (uiKeyCode == KEY_NONE && !Pause) {
      uiKeyCode = uiKeyCodeFirst;
      PrevTime2 =  millis();
      Pause = 1;
    }
    else if (Pause)
    {
      uiKeyCode = KEY_NONE;
    }
    NewTime2 = millis();
    if ((NewTime2 - PrevTime2) >= 500UL) {
      uiKeyCode = uiKeyCodeFirst;
    }
  }
  else {
    Pause = 0;
    uiKeyCode = KEY_NONE;
    //Serial.println("Opt 3");
  }
}

void KeyEvent(int Key, boolean Pos) {
  switch (Key) {
    case PUSHSW1 :
      if (Pos) PUSHSWA = 1;
      else PUSHSWA = 0;
      KeyActive = 1;
      break;
    case PUSHSW2 :
      if (Pos) PUSHSWB = 1;
      else PUSHSWB = 0;
      KeyActive = 1;
      break;
  }
  // Serial.println(String(PUSHSWA) + "\t" + String(PUSHSWB));
}

void Trim() {
  for (int i = 0; i < TOTALSWITCHES - 2; i++) {
    if (SwitchPrev[i])
    {
      if (i < 4) {
        StickTRIM[i]-- ;
         StickTRIM[i] = constrain(StickTRIM[i], -150, 150);
        eeprom_write_int(CHANNELS * 10 + i + 1,  StickTRIM[i]);
        //Serial.println(String(i) + "\t");
      }
      else if (i >= 4) {
        StickTRIM[i-4]++ ;
        StickTRIM[i-4] = constrain(StickTRIM[i-4], -150, 150);
        eeprom_write_int(CHANNELS * 10 + i - 4 + 1, StickTRIM[i-4]);
        //Serial.println(String(i) + "\t");
      }
    }
  }
}


void SWPos(void) {
  if ( analogRead(SWAPin) < 250 )
    SWA = MODE_ONE;
  else if ( analogRead(SWAPin) > 250 && analogRead(SWAPin) < 750 )
    SWA = MODE_TWO;
  else if (analogRead(SWAPin) > 750 )
    SWA = MODE_THREE;

  if ( analogRead(SWBPin) < 250 )
    SWB = MODE_ONE;
  else if ( analogRead(SWBPin) > 250 && analogRead(SWBPin) < 750 )
    SWB = MODE_TWO;
  else if (analogRead(SWBPin) > 750 )
    SWB = MODE_THREE;

}


