void setup() {
  // put your setup code here, to run once:
  startup();
}

void loop() {
  // put your main code here, to run repeatedly:

}
//global data
  int startupBlink = 10;
  int waterTank = 2;
  int foodTank = 1; 
  //set values for time
///NOTE: Plz adjust time here///
///*** 1000 is equal to 1 sec ****
double startTime = millis(); // getting time at start
double pour = 5000 /// the time solenoid is active


//***Subsystems***
//Food Dispenser
//Water Dispenser
//Automation
//Scale
//Sensors
//Speakers
//LCD Screen
//
//

//***main***
//


// basically the setup() function above
void startup(){
  // Purpose: the to create state where the board fetches saves information 
  ////and checks essential process before moving on to the next state 

  // intiate pins



  pinMode(PA2,OUTPUT);// intializing water dispensor pin
  pinMode( ??,INPUT);// intializing water sensor pin **** FIND THE PIN OF THE SENSOR
  pinMode(LED,OUTPUT);// intializing Water system LED
  delay(15000); // 15s
    /// meanwhile LED will indicate start-up
    /// will hold LED state for 1 sec
  for(i=0;i < startBlink;i++){
    delay(1000)
    digitalWrite(LED,HIGH);
    delay(1000);
    digitalWrite(LED,LOW);
  }
  //**fetching data - feature** needs to access flash memory
}

void checkLevels(){
//Purpose: checking tanks and flag errors
// errors are gonna be sent to LCD and/ or LED lights one LED indicates Water levels the other Food levels


}


void measureAndDispense(){
  // stub


}

void manual(){ // user controls the amount dispense
  // stub
}



// one isEmpty funtion that calls ------ could possible also fit in for 
bool isEmpty(source){
  bool empty = false;
  switch(source){
    case 1:
      if(waterSensor() == true){// checking sensor -> returns boolean
          empty = true;
      }
    case 2:
      if(foodSensor() == true){// checking sensor -> returns boolean
          empty = true;
      }
    default:
          empty = false;
  }
  return empty;
}
bool scale(){// checks sensor information
  //stub
}


void waterDispenser(){
  digitalWrite(PA2,HIGH);
  delay(pour);
  digitalWrite(PA2,LOW);
}

void foodDispenser(){
  //stub
}
bool foodSensor(){// checks sensor information
  bool ifEmpty = 0;
  if(digitalRead(??)== HIGH){ /// NOTE: food IR sensor  // stub
    ifEmpty = true;
    }
  else(){
    ifEmpty = false:
    }
  return ifEmpty;
}

bool waterSensor(){// checks sensor information
  bool ifEmpty = 0;
  if(digitalRead(??)==HIGH){ /// NOTE: needs to verify empty tank is high or low 
    ifEmpty = true;
    }
  else(){
    ifEmpty = false:
    }
  return ifEmpty;
}
  
