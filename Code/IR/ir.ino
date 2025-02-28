#define PINIR PIN_PA3 // PA3
#define PINLED PIN_PD3 // PD3

void setup() {
  pinMode (PINIR, INPUT);
  pinMode (PINLED, OUTPUT);
  analogReference(DEFAULT);
//  Serial.begin(9600);
}

void loop() {
  // variables
  int distanceCM, median, LEDistance;
  float current;
  int ir_val[25] = {};
  
  // Gather samples
  for (int i=0; i<25; i++){
      ir_val[i] = analogRead(PINIR);
  }
  
  // Sort Samples
  for(int i=0; i<(25-1); i++) {
      bool flag = true;
      for(int o=0; o<(25-(i+1)); o++) {
          if(ir_val[o] > ir_val[o+1]) {
              int t = ir_val[o];
              ir_val[o] = ir_val[o+1];
              ir_val[o+1] = t;
              flag = false;
          }
      }
      if (flag) break;
  }
  
  // get mid value
  median = ir_val[25/2];
  
  // disctance calculations
  distanceCM = 29.988 * pow(map(median, 0, 1023, 0, 5000)/1000.0, -1.173); 

  // led on when read +20cm
  if(distanceCM > 20){
    digitalWrite(PINLED, HIGH);
    delay(1000);
    }
  else{
    digitalWrite(PINLED, LOW);
    delay(1000);
      }
}
