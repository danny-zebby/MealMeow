//Number of steps in the motor for one rotation
#define STEPS 516 //2038

//Stepper Driver Pins
#define RESET  PIN_PA7    //5 Reset Pin, active high to reset
#define ENABLE PIN_PC0    //6 Enable pin, active low to enable
#define FAULT  PIN_PA6    //4 Fault pin, stepper driver outputs a 1 if there is some issue

/*
//Motor to board connections

Blue == P2B == PIN_PC1 == bottom input on board
Pink == P2A == PIN_PC2


Red == VDD

Yellow == P1B == PIN_PC3
Orange == P1A == PIN_PD0

*/

#define P1A PIN_PD0
#define P1B PIN_PC3
#define P2A PIN_PC2
#define P2B PIN_PC1

#define stepperDelayMicroSeconds = 100;



void StepOnceBackward(){
  delay(stepperDelayMicroSeconds);
  //STEP 1
  digitalWrite(P1A, LOW);
  digitalWrite(P1B, HIGH);
  digitalWrite(P2A, HIGH);
  digitalWrite(P2B, HIGH);
  delay(stepperDelayMicroSeconds);
  //STEP 2
  digitalWrite(P1A, HIGH);
  digitalWrite(P1B, LOW);
  digitalWrite(P2A, HIGH);
  digitalWrite(P2B, HIGH);
  delay(stepperDelayMicroSeconds);
  //STEP 3
  digitalWrite(P1A, HIGH);
  digitalWrite(P1B, HIGH);
  digitalWrite(P2A, LOW);
  digitalWrite(P2B, HIGH);
  delay(stepperDelayMicroSeconds);
  //STEP 4
  digitalWrite(P1A, HIGH);
  digitalWrite(P1B, HIGH);
  digitalWrite(P2A, HIGH);
  digitalWrite(P2B, LOW);
  delay(stepperDelayMicroSeconds);  
}

void StepOnceForward(){
  delay(stepperDelayMicroSeconds);
  //STEP 4
  digitalWrite(P1A, HIGH);
  digitalWrite(P1B, HIGH);
  digitalWrite(P2A, HIGH);
  digitalWrite(P2B, LOW);
  delay(stepperDelayMicroSeconds);
  
  //STEP 3
  digitalWrite(P1A, HIGH);
  digitalWrite(P1B, HIGH);
  digitalWrite(P2A, LOW);
  digitalWrite(P2B, HIGH);
  delay(stepperDelayMicroSeconds);

  //STEP 2
  digitalWrite(P1A, HIGH);
  digitalWrite(P1B, LOW);
  digitalWrite(P2A, HIGH);
  digitalWrite(P2B, HIGH);
  delay(stepperDelayMicroSeconds);
  
  //STEP 1
  digitalWrite(P1A, LOW);
  digitalWrite(P1B, HIGH);
  digitalWrite(P2A, HIGH);
  digitalWrite(P2B, HIGH);
  delay(stepperDelayMicroSeconds);  
}

void StepperSetup() {
  pinMode(RESET, OUTPUT); //Reset Pin, active high to reset
  digitalWrite(RESET,LOW);
  
  pinMode(ENABLE, OUTPUT);  //Enable pin, active low to enable
  digitalWrite(ENABLE, LOW);

  pinMode(FAULT, INPUT);

  pinMode(P1A, OUTPUT);
  pinMode(P1B, OUTPUT);
  pinMode(P2A, OUTPUT);
  pinMode(P2B, OUTPUT);
}

void DispenseFood() {
  for (int i = 0; i < 8; i++){
    StepOnceForward();
  }
  for (int i = 0; i < 4; i++){
    StepOnceBackward();    
  }
}
