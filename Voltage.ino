void Batt(){
  total -= ( readings[readIndex] );
  readings[readIndex] = (float)analogRead(BATT)* 5.0 / (float)VoltageDiv;
  total += readings[readIndex];
  readIndex += 1;
  if (readIndex >= numReadings)readIndex = 0;
  average = total / numReadings;
}
