 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

  const int buttonPin = 2;
  const int upPin = 3;
  const int downPin = 4;

  int buttonState = 0;
  int upButtonState = 0;
  int downButtonState = 0;

  String OP = "";

void display1(){
  while(true){
    lcd.setCursor(1, 0);
    lcd.print("    MealMeow    ");
    lcd.setCursor(1, 1);
    lcd.print("Hit sel to cont.");
    delay(3000);
    lcd.clear();
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW){
      break;
    }

    lcd.setCursor(2, 0);
    lcd.print("   Hungry? ");
    lcd.setCursor(2, 1);
    lcd.print("   Thirsty?");
    delay(3000);
    lcd.clear();
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW){
      break;
    }
  }
}

float grams = 0;                                            //Caution not to use "grams" as variable in load cell code. Maybe rename? Maybe a non-issue due to the variable scope.
float gramStepSize = 10;                                   
void display2(){
  while(true){
    
    downButtonState = digitalRead(downPin);
    upButtonState = digitalRead(upPin);
    buttonState = digitalRead(buttonPin);
    
    if(upButtonState == LOW){
      grams = grams + gramStepSize;                       //2 cats need ~280g cat food per day. We should increase to 10g increments
      if (grams > 250){
        grams = 250;
      }
    }

    
    if(downButtonState == LOW){
      grams = grams - gramStepSize;
      if(grams < 0){
        grams = 0;
      }
    }
    
    if(buttonState == LOW){
      break;
    }

    lcd.setCursor(0, 0);
    lcd.print("How many grams");
    lcd.setCursor(0, 1);
    lcd.print("to dispense:");
    lcd.print(grams);
    lcd.print("g");
    delay(3000);
    lcd.clear();

    
    
  }
}

int sel = 0;
void display3(){
  while(true){
    downButtonState = digitalRead(downPin);
    upButtonState = digitalRead(upPin);
    buttonState = digitalRead(buttonPin);
    
    if(upButtonState == LOW){
      sel = sel + 1;
    }

    
    if(downButtonState == LOW){                    //Should this be downButtonState?
      sel = sel - 1;
      if(sel < 0){
        sel = 0;
      }
    }
    int select = sel%2;
    if (select == 0){
      OP = "Interval";
    }else{
      OP = "On Demand";
    }
    
   if(buttonState == LOW){
      break;
    }
    lcd.setCursor(0, 0);
    lcd.print("Sel DispenseMode");
    lcd.setCursor(0, 1);
    lcd.print(OP);
    delay(3000);
    lcd.clear();
    
    
  }
}

int interval = 0;
void display4(){
  while(true){
    upButtonState = digitalRead(upPin);
    if(upButtonState == LOW){
      interval = interval + 1;
    }

    downButtonState = digitalRead(downPin);
    if(downButtonState
    +6== LOW){
      interval = interval - 1;
      if(interval < 0){
        interval = 0;
      }
    }

    lcd.setCursor(0, 0);
    lcd.print("Dispense next in");
    lcd.setCursor(0, 1);
    lcd.print(interval);
    lcd.print("mins");
    delay(3000);
    lcd.clear();
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW){
      break;
    }
  }
}

void display5(){
  lcd.setCursor(1, 0);
  lcd.print("Food grams:");
  lcd.print(grams);
  lcd.print("g");
  lcd.setCursor(1, 1);
  lcd.print("Interval:");
  lcd.print(interval);
  lcd.print("min");
}

void display6(){
  lcd.setCursor(1, 0);
  lcd.print("    MealMeow    ");
  lcd.setCursor(1, 1);
  lcd.print("Hit sel to disp.");
}

void setup() {
  begin(DOUT, PD_SCK);
  SCALE = -812.859; // change this value // it's a defualt value
  tare();               // reset the scale to 0

  // put your setup code here, to run once:
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
  pinMode(buttonPin ,INPUT);
  pinMode(upPin ,INPUT);
  pinMode(downPin ,INPUT);
  StepperSetup();     //Intializing motors
  display1(); // Intro screen
  lcd.clear();
  delay(1000);
  display2(); // Asking for how many grams
  lcd.clear();
  delay(1000);
  display3(); // Asking for dispensing Mode
  lcd.clear();
  delay(1000);
  
  if (OP == "Interval"){
    display4(); // How long to interval
    lcd.clear();
    delay(1000);
    display5(); // Forever
  }
  else{
    display6();  // Forever
  }
  
  boolean temp = TRUE;
  while(temp){
    DispenseFood(); // needs scaling
    float trace = get_units(1);
    if (trace >= grams){
      temp = false;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(OP == "Interval"){
      for(int times = interval * 60; times > 0; times--){
      buttonState = digitalRead(buttonPin);
      if(buttonState == LOW){
         DispenseFood(); // just dispense, no scale check
      }
      delay(1000);
    }
    DispenseFood(); // needs scaling
  }else{
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW){
      DispenseFood(); // just dispense, no scale check
    }
  }
  
  
}
