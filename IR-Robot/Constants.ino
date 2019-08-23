#ifndef Constants_h
#define Constants_h 

class Constants {
	private:
		void setup();
	public:
		String mapIRCode(int inputCode);
		Constants() {
			setup();
		}
};
String Constants::mapIRCode(int inputCode) {
		switch(inputCode) {
			case 0xFF18E7: //BUTTON_UP
			Serial.print(inputCode + " BUTTON_UP");
				return "BUTTON_UP";
			break;
			case 0xFF4AB5: //BUTTON_DOWN
				Serial.print(inputCode + " BUTTBUTTON_DOWNON_UP");
				return "BUTTON_DOWN";
			break;
			case 0xFF10EF: //BUTTON_LEFT
				Serial.print(inputCode + " BUTTON_LEFT");
				return "BUTTON_LEFT";
			break;
			case 0xFF5AA5: //BUTTON_RIGHT
				Serial.print(inputCode + " BUTTON_RIGHT");
				return "BUTTON_RIGHT";
			break;
			default: //error
				Serial.print(inputCode + " unknown button ");
				return "error_code";
			break;
		}
}
void Constants::setup() {
}
#endif