
string prompt [3] = {"Amount of per Day"," ","are you sure"};
bool lowWater = false;// for pouring
bool lowFood = false;
bool isZero = false;
long startSystem = millis();// first time 
long currentTime = 0; //time of measure
long setTime = 0; // interval to wait
int grams = 0;

int maxValue = NULL;// needs to up date************!!!!!

bool needsReset = false;
int mL = 4000;// 4s for x ml when dispensing liquid
////Four sides

//PINOUT//UPPER--pins(32-24)
pinMode(PA2,OUTPUT);//SOLENOID
PinMode(PA1,INPUT_PULLUP);//Button1
//pinMode(PF6,INPUT);//Reset

//RightMost--pins(22,25,24)
pinMode(PF2,INPUT_PULLUP);//Button2
pinMode(PF5,OUTPUT);//LCD 1(..)
pinMode(PF4,OUTPUT);//LCD 2(..)

//LOWER--pin(13-7)
pinMode(PD3,INPUT);//WaterSensor
pinMode(PD2,INPUT_PULLUP);//Button3
pinMode(PD1,OUTPUT);//Speaker
//Motor Pins
pinMode(PD0,OUTPUT);//1
PinMode(PC3,OUTPUT);//2

//LeftMost--Pin(8-1)
pinMode(PC2,OUTPUT);//3
pinMode(PC1,OUTPUT);//4

pinMode(PC0,OUTPUT);// en
pinMode(PA7,OUTPUT);//motor reset
pinMode(PA6,??)://FAULT

//SCALE
pinMode(PA5,??);//SCK 
pinMode(PA4,??);//DAT

pinMode(PA3,INPUT);//FoodSensor /// look how it works with interrupts

/////******MENU******/////
//// Interrupts global

volatile int center = 0;

volatile bool confirm = 0;

volatile bool emptyBox = false;

attachInterrupt(digitalPinToTnterrupt(PA1),upOne,CHANGE);
attachInterrupt(digitalPinToTnterrupt(PA1),downOne,CHANGE);
attachInterrupt(digitalPinToTnterrupt(PA1),select,CHANGE);

attachInterrupt(digitalPinToTnterrupt(PD3),empty,LOW);// switch goes low interrupt activates

////IRS////

void upOne(){ /// for menu
    center++;
}
void downOne(){
    center--;
}
void select(){
    confirm =!confirm;
}
void empty(){ /// no food or water
    needsReset = !needsReset;
}


////****LED****////
void display1(){
  while(confirm){
    lcd.setCursor(1, 0);
    lcd.print("    MealMeow    ");
    lcd.setCursor(1, 1);
    lcd.print("Hit sel to cont.");
    delay(3000);
    lcd.clear();
  
    lcd.setCursor(2, 0);
    lcd.print("   Hungry? ");
    lcd.setCursor(2, 1);
    lcd.print("   Thirsty?");
    delay(3000);
    lcd.clear();
  }
}
void display2(){
  while(confirm){
    int grams = grams + center;
    if(grams < 0){
        grams = 0;
      }
    center = 0; 
    lcd.setCursor(0, 0);
    lcd.print("How many grams");
    lcd.setCursor(0, 1);
    lcd.print("to dispense:");
    lcd.print(val2);
    lcd.print("g");
    delay(3000);
    lcd.clear();
  }
}

////*****Speaker****/////

void playSound(){
  tone(PD1,784,4000);
}

////***Zero Scale***////
void  zero(){
    //stub
  }

///Motors///
void motor(){
  //stub
}
/// solenoid///
void solenoid(){
  digitalWrite(PA2,HIGH);
  delay(mL);
  digitalWrite(PA2,LOW);
}

////***Looping Process***////

  void weigh(){
    //stub
  }
  void pour(String val){
    if(val=="water"){
      solenoid();
    }
    if(val=="food"){
      motor();
    }
  }


//.....goes in loop()
while(needsReset){
  noInterrupts();
  playSound();
  int button = digitalRead(PA1);
  if (button == HIGH){
    needsReset = !needsReset;
    interrupts();
  }
}
  if(isZero){
    weigh();
  }
if (!maxValue){
  if(lowWater){
    pour("water");
  }
  if(lowFood){
    pour("food");
  }
}


// void setup() {
//   // put your setup code here, to run once:
display1();
confirm =!confirm();
display2();
confirm =!confirm();

// }

// void loop() {
//   // put your main code here, to run repeatedly:

// 
  
