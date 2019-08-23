
#include "Constants.ino"
 
#ifndef DisplayController_h
#define DisplayController_h 

LiquidCrystal lcd(LCD_rs, LCD_en, LCD_d4, LCD_d5, LCD_d6, LCD_d7);

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