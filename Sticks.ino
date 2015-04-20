void StickCalc() {
  for (int i = 0; i <  CHANNELS; i++) {
    switch (i) {
      case 0:
      case 1:
      case 3:
        if (AnalogRead(PIN[i]) < (StickMid[i] - Deadband)) StickVal[i] =  map(AnalogRead(PIN[i]), StickMin[i], StickMid[i] - Deadband, -500, 0);
        else if (AnalogRead(PIN[i]) > StickMid[i] + Deadband) StickVal[i] =  map(AnalogRead(PIN[i]), StickMid[i] + Deadband, StickMax[i], 0, 500);
        else StickVal[i] = 0;
        break;
      case 2:
      case 4:
      case 5:
        StickVal[i] =  constrain(map(AnalogRead(PIN[i]), StickMin[i], StickMax[i], -500 , 500),-500,500);
        break;
    }
     //Serial.print(String( StickVal[i]) + "\t");
  }
  //Serial.println("");
}
/*
void SwitchPos() {
  if (analogRead(SWA))
  {
    SWA = 1;
  }
  else if (!digitalRead(SWA2))
  {
    SWA = 2;
  }
  else
  {
    SWA = 0;
  };
  if (!digitalRead(SWB1))
  {
    SWB = 1;
  }
  else if (!digitalRead(SWB2))
  {
    SWB = 2;
  }
  else
  {
    SWB = 0;
  };
}*/

void SwitchCalc() {
  switch (SWA) {
    case MODE_ONE :
      StickVal[6] = -500;
      break;
    case MODE_TWO :
      StickVal[6] = -200;
      break;
    case MODE_THREE :
      switch (SWB) {
        case MODE_ONE :
          StickVal[6] = -90;
          break;
        case MODE_TWO :
          StickVal[6] = 50;
          break;
        case MODE_THREE :
          StickVal[6] = 500;
          break;
      }
      break;
  };
}
