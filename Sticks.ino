void StickCalc() {
  for (int i = 0; i <  CHANNELS; i++) {
    switch (i) {
      case 0:
      case 1:
      case 3:
        if (analogRead(PIN[i]) < (StickMid[i] - Deadband)) StickVal[i] =  map(analogRead(PIN[i]), StickMin[i], StickMid[i] - Deadband, 0, 500);
        else if (analogRead(PIN[i]) > StickMid[i] + Deadband) StickVal[i] =  map(analogRead(PIN[i]), StickMid[i] + Deadband, StickMax[i], 500, 1000);
        else StickVal[i] = 500;
        break;
      case 2:
      case 4:
      case 5:
        StickVal[i] =  constrain(map(analogRead(PIN[i]), StickMin[i], StickMax[i], 0 , 1000),0,1000);
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
      StickVal[6] = 0;
      break;
    case MODE_TWO :
      StickVal[6] = 300;
      break;
    case MODE_THREE :
      switch (SWB) {
        case MODE_ONE :
          StickVal[6] = 410;
          break;
        case MODE_TWO :
          StickVal[6] = 550;
          break;
        case MODE_THREE :
          StickVal[6] = 1000;
          break;
      }
      break;
  };
}
