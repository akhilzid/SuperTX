void StickCalc() {
  StickCycle ++;
  //if (StickCycle > CHANNELS) StickCycle  = 0;
  //int i = StickCycle;
  for (int i = 0; i <  CHANNELS; i++) 
  {
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
  // Serial.println(String(SWA) + "\t" + String(SWB));
}
