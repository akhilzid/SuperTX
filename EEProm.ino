void getData()
{
  for (int i = 0; i < CHANNELS; i++) {
    ppm[i] = default_servo_value;
  }
  ppm[2] = 1000;
  GapTime = eeprom_read_int(CHANNELS * 9 + 2);
  VoltageDiv = eeprom_read_int(CHANNELS * 9 + 3);
  Deadband = eeprom_read_int(CHANNELS * 9 + 4);
  
  for (int i = 0; i < CHANNELS; i++) {
    CH[i] = eeprom_read_int(CHANNELS * 2 + i + 1);
    CH_Reversed[i] = eeprom_read_int(CHANNELS * 3 + i + 1);
    CH_EMIN[i] = eeprom_read_int(CHANNELS * 4 + i + 1);
    CH_EMAX[i] = eeprom_read_int(CHANNELS * 5 + i + 1);

    StickMin[i] = eeprom_read_int(CHANNELS * 6 + i + 1);
    StickMid[i] = eeprom_read_int(CHANNELS * 7 + i + 1);
    StickMax[i] = eeprom_read_int(CHANNELS * 8 + i + 1);
    
    StickTRIM[i] = eeprom_read_int(CHANNELS * 10 + i + 1);
  }
};

void setData()
{
  for (int i = 0; i < CHANNELS; i++) {
    eeprom_write_int(CHANNELS * 2 + i + 1, CH[i]);
    eeprom_write_int(CHANNELS * 3 + i + 1, constrain(CH_Reversed[i], 0,1));
    eeprom_write_int(CHANNELS * 6 + i + 1, constrain(StickMin[i],0,200));
    eeprom_write_int(CHANNELS * 7 + i + 1, constrain(StickMid[i],400,600));
    eeprom_write_int(CHANNELS * 8 + i + 1, constrain(StickMax[i],800,1000));
  }
};

void SaveEP()
{
  for (int i = 0; i < CHANNELS; i++) {
    eeprom_write_int(CHANNELS * 4 + i + 1, CH_EMIN[i]);
    eeprom_write_int(CHANNELS * 5 + i + 1, CH_EMAX[i]);
  }
};

void SaveDefault()
{
  eeprom_write_int(CHANNELS * 9 + 2, 40);
  eeprom_write_int(CHANNELS * 9 + 3, 511);
  eeprom_write_int(CHANNELS * 9 + 4, 3);
  
  for (int i = 0; i < CHANNELS; i++) {
    eeprom_write_int(CHANNELS * 2 + i + 1, 1);
    eeprom_write_int(CHANNELS * 3 + i + 1, 0);
    
    eeprom_write_int(CHANNELS * 4 + i + 1, 0);
    eeprom_write_int(CHANNELS * 5 + i + 1, 1000);
    
    eeprom_write_int(CHANNELS * 6 + i + 1, 0);
    eeprom_write_int(CHANNELS * 7 + i + 1, 500);
    eeprom_write_int(CHANNELS * 8 + i + 1, 1000);
    
    eeprom_write_int(CHANNELS * 10 + i + 1, 500);
  }
}


void eeprom_write_int(int i, int v) {
  
  EEPROM.write(i*2, highByte(v));
  EEPROM.write((i*2)+1, lowByte(v));
}

int eeprom_read_int(int i) {
  return word(EEPROM.read(i*2),EEPROM.read((i*2)+1));
}
