// Segments map of display
//
//		A
//     ---
//	F |   | B
//	   -G-
//	E |   | C
//	   ---
//		D
//
#include "Constants.ino"
 
#ifndef DisplayController_h
#define DisplayController_h 

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Definition of numbers to be shown with colon in the display
uint8_t dataWithColon[] = {
  0b10111111, // 0
  0b10000110, // 1
  0b11011011, // 2
  0b11001111, // 3
  0b11100110, // 4
  0b11101101, // 5
  0b11111101, // 6
  0b10000111, // 7
  0b11111111, // 8
  0b11101111, // 9
  0b00000000, // 10
};


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
  lcd.setCoursor(x, y);
  lcd.print(message);      
}

void DisplayController::clear() {
  lcd.clear();
}

#endif