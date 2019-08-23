
#include "Constants.ino"
 
#ifndef DisplayController_h
#define DisplayController_h 

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

class DisplayController {
	private:
		void setup();
	public:
		void displayMessage(String message, int x = 0, int y = 0);
		void clear();
		DisplayController() {
			setup();
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