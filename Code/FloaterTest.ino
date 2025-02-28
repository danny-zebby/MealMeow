void setup() {
  pinMode(2,INPUT);//WaterSensor  // to replace for the one for PCB which is pinMode(PD3,INPUT);
  pinMode(3,OUTPUT); // led for testing
}

void loop() {
  int val = digitalRead(2);
  digitalWrite(3,val);
}
