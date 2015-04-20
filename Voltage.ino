void Batt(){
  total -= ( readings[readIndex] );
  readings[readIndex] = (float)analogRead(BATT)* 5.0 / (float)VoltageDiv;
  total += readings[readIndex];
  readIndex += 1;
  if (readIndex >= numReadings)readIndex = 0;
  average = total / numReadings;
}

/*void Batt() {
  sensorValue = analogRead(BATT);
  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 1023);
  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 1023);
  //return (float)analogRead(BATT) * 5.0 / 511.5;
}*/
/*
long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0) ;
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif

  //delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  long result = (high << 8) | low;

  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}*/
