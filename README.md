# MealMeow

## General Description
The general concept of this design seeks to solve the problem of caring for your cats or dogs while you are away for an extended period of time. Our aim is to create a product that can handle the feeding and hydrating of several pets while the owner is away. We will create a device that will dispense water, and food to pets at amounts configurable by the owner at regular intervals and it will do so independently. Our product will only require the attention of the owner when any of the aforementioned items is depleted. When food has run low, or when any of the dispensable items have run out, our device will alert the owner using sound alerts and a warning indicator light.

## Behavioral Specification
### Food Storage and Dispensation
Food will be stored in a container and will be dispensed using a rotating paddle at the bottom of the container. We intend to control this rotating paddle using a direct-current stepper motor. The food container will be equipped with a IR distance sensor placed at one side of the container, once the IR distance sensor measures the other side of the container, it will be known that there is no food at that level. This will cause the unit to light an LED as a low food level indicator for the user. As an alternative, another sensor can be reading the distance between the sensor and what’s in front. 
Once the food level sensor measures that the container is low on food, our product will notify the user of low food levels. A flashing LED will turn on when a sensor has indicated low levels, the LED will be color coordinated depending on the container. We aim for our product to use a speaker to alert the user with either a tone or voice.

### Water Storage and Dispensation
Our device will store water in a large water bladder connected to a motorized water solenoid valve, which will control the flow of water from the reservoir and through tubing ending in the pet’s water bowl.

### Food and Water Measuring
Our product will be equipped with pressure sensors below the surface where the food and water bowls are placed. We intend to use either digital load cell weight sensors or strain gauges to sense the weight placed on the food and water bowls. The unit will calculate the amount of food or water that has been dispensed by calculating the difference in pressure at the food and water bowls.

### User Interface
User interface will consist of 3 buttons and a 20x2 LCD screen. The unit will have 2 “modes” which will allow the user to program the unit. When the “food” mode is engaged, the screen will display the amount of food that is to be dispensed daily. From this mode, the user can use two of the buttons to increment and decrement the amount of food to be dispensed in increments of 10g. This will allow the user to relatively precisely control the amount of food the pet receives each day in order to ensure the pet remains at a healthy weight. 



## Subsystem Control
### Water Dispenser
Components: 
Plastic Water Solenoid Valve - 12V - 1/2" Nominal (adafruit 997)
Darlington Transistor TIP-120

Description:
Plastic valve with solenoid that is activated with power.Solenoids activates when current is passed Max voltage is 12 V. It is one way flow and is suggested to use a TIP 120 to drive from a MCU. The amount of time active or water being dispensed will be determined by trial and error.

### Food Dispenser Control
Component Name: Small Reduction Stepper Motor 12V 
Adafruit Product ID 918

Description
	This stepper motor works on DC power. We chose this motor to operate the food dispenser mechanism because stepper motors like this one are geared to move at approximately rotation “steps”, which will allow us to more accurately control flow of food into the pet’s food bowl, which is an important part of our design. This particular stepper motor has 516 steps. This type of motor also holds its position strongly, which is important for the dispersal mechanism so that the mechanism does not rotate under the weight of the pet’s food. This type of motor is controlled by sending electrical pulses which instruct the motor to turn one step. A motor driving circuit is necessary to operate this motor. 

### Food Storage Level Sensor Control
Component Name: Infrared Proximity Sensor - Sharp GP2Y0A21YK

Paragraph description:
This infrared proximity sensor will be placed at a low enough in the container to sense when the food is near empty, but also high enough for the pet to have one or two more bowls. As long as the product is on the infrared sensor is also on. The infrared sensor is emitting an infrared light that bounces back into the built infrared sensor. After doing some math for how long it took the sensor to submit and receive the light, it calculates the distance of what’s in front of it. If the distance measure is the diameter of the container, then it is known there’s no food across the sensor, marking the container low. If the sensor measures anything less than the diameter then it will be known that the container has enough food before refilling.
	An infrared sensor was selected because it was better at reading non flat surfaces, which is perfect for pet food. According to the datasheet, the sensor has trouble being accurate for low levels. Which is not a concern for our purposes since we do not need to know the exact distance from the sensor to the, we just need to know the distance from the sensor to the container. My understanding of the infrared proximity sensor coding is that it sorts 25 samples of analogread, then it takes the median from those samples. Then maps it 0 to 5000, divides by 5000, takes that to the power of -1.2045 and finally multiplies to 27.728. This equation gives us the conversion from Voltage to centimeters.

### Water Reservoir Level Sensor Control / Standard Level Sensor(alternative) 
Component Name: SEN0509 - Capacitive pipeline liquid level sensor
			PLS-051B-3PPI-Standard Level Sensor (in case other sensor fails)

Description: 
	Meant for non-metallic pipes, made with plastic, and signals low when water is present. It’s range is from 2.5 - 5.5V. Can be used to detect the level of water either high or low water level. Signal will go directly to a general purpose I/O connection on a MCU.Sensor is going to placed near the bottom of the tank, connected with two line tubes 6mm of diameter. The tube will be connected to the tank from the bottom and the other end will be attached to the top of the tank, capped off to prevent spillage.

Alternatively, the standard level sensor can be used just in case the other sensor stops working. This sensor will receive power and pass through and once the water level reaches a low state them.The relay will switch to no power pass through. For this component, it has a large capability to handle 200V at 1 A.Hence, it will operate at 5.5V for convenience that other water sensor component max is at 5.5V.

### Food Scale Sensor Control
Component Name: Strain Gauge + HX711

Description:
The MealMeow uses two strain gauges attached to two boards for where the pet’s bowl to be placed on. The project uses user input, via the LED screen, to determine how much of a serving of food and water the bowls should have. Once the MealMeow is ready to dispense either the food or water, it will measure the current weight of the board and bowl, then will dispense until it reaches the desired amount of grams. 
For our purposes the usage of the Strain Gauge is simple, however implementation of the HX711 proves difficult. We are considering alternative methods for this chip. The main usage of the chip is a 64 or 128 gain followed by a 24 bit Analog-to-Digital Converter (ADC). The HX711 has an input MUX and a digital interface that uses the clock to read the 24 bits. The HX711 datasheet has transistors parts, capacitors and resistors with the build for the purposes for using the strain gauges we plan on using.

## Power Supply
Components:
Switching Regulator, LTC3601 from Linear Technology
AC/DC Wall Adapter, Tensility International Corp 16-00031

This project will utilize two voltage regions on the PCB, at 12V and at 5V. The processor and most peripherals will utilize the 5V region, and the water and food dispensal motors will operate using the 12V region. In order to supply power to the PCB, we will use an AC to DC wall adapter from. This wall adapter will supply our board with 12 volts of DC power. We then intend to use a switching regulator to construct a step-down circuit which will output 5V of power.
Microprocessor: 
ATMEGA4808-XF

Description: 
The Microprocessor we decided to use for our project is the ATMEGA4808-XF. This microprocessor is an 8-bits fits our needs as it provides adequate speed, memory, and ports our project needs. The MealMeow’s functionality does not not rely on speed, so the 20MHz this chip provides is plenty for our purpose. This chip also has various connectivity ports, including I^2C. We plan on using I2C as our peripherals and interfaces do not all need to be working all at once. The ATMEGA4808-XF was ultimately chosen over other similar chips due to the expansion in flash memory, sufficient number of ports, and price. We have the flexibility of adding features if necessary, storing text and storing audio.

Attributes:
Voltage: 1.8V ~ 5.5V
Temperature: -40℃ ~ 125℃
Core Size: 8-Bit
Speed: 20MHz
Clock Cycle: Max 20MHz at 4.5V ~ 5.5V
Flash Memory Size: 48KB
Peripherals: 3x UART, 1x SPI, 1x I2C

## Speaker Output Control
Component Name: SPEAKER 8OHM 2W TOP PORT 84DB - 
2223-CMS-402811-28SP-ND
Description:
This general purpose speaker has a frequency range between 300 Hz and 20 kHz. The main focus of this speaker was so that you will be able to hear it from a fairly large amount of distance between you and the speaker. This will be connected to the straight from the processor since we do not intend to project sound at a high volume.

## LCD screen
Component Name: LED Character Display.  
LCD MOD 40DIG 20X2 TRANSFLCT WHT - NHD-C0220BIZ-FSW-FBW-3V3M-ND

Description: 
This LED - yellow/green character display will have 2 lines x 20 characters and its character format is 5 x 8 dots. The interface that I will be using is I2C. Since I will be using I2C there will only be two pins I will be using. This also has a built-in DC supply for VLCD. The only thing that this display needs to get connected to is the processor since it already has power.

## Software
### Processor (Software) ATMEGA4808-XF:
Booting Modes: (Page 465 of Datasheet)
Programing: To program our chip, we will be using a hardware programer: Pocket AVR Programmer . Using the software Arduino Bootlander, the chip should be able to boot into an operabl;e state. Bootloader is the software used in Arduinos when you press the reset and ON button. This microprocessor should be compatible with Bootlander as it is part of the ATMEGA Arduino family. 


## Conclusion
As a group, we had a clear purpose, to make the best cat feeder we could make. Our group leader, Christian Leon, has two cats he loves and adores. One of the components of our senior project that as a group we had decided was of priority to all of us was to ensure our project had a purpose. The MealMeow archives this by ensuring Christians cats will have the best dining experience we can make. All of the components and features of the MealMeow have taken into consideration the sensibilities and comfort of a cat. When the project was in its early stages, the task seemed quite intimidating. Now that we are in this stage and have our features and components selected, we are excited to see the MealMeow in action soon. We expect troubles and difficulties ahead, but are excited to confront these challenges.
