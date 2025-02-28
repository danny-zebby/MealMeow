#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
int val2 = 150;
void setup()
{
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("How many grams");
  lcd.setCursor(0, 1);
  lcd.print("to dispense:");
  lcd.print(val2);
  lcd.print("g");
  delay(3000);
  lcd.clear();
}
