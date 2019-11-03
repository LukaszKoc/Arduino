
#include <LiquidCrystal.h>
 
#ifndef DisplayController_h
#define DisplayController_h 

LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

class DisplayController {
	private:
	public:
		void setup();
		void displayMessage(String message, int x = 0, int y = 0);
		void clear();
		DisplayController() {
		}
}; 

void DisplayController::setup() {
 	  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("");			
}

void DisplayController::displayMessage(String message, int x = 0, int y = 0) {
  lcd.setCursor(x, y);
  lcd.print(message);      
}

void DisplayController::clear() {
  lcd.clear();
}

#endif