#ifndef Constants_h
#define Constants_h 

class Constants {
	private:
	public:
		void setup();
		String mapIRCode(int inputCode);
		Constants() {
		}
};
String Constants::mapIRCode(int inputCode) {
		switch(inputCode) {
			case 0xFF18E7: //BUTTON_UP
			Serial.println("Constants: BUTTON_UP " + inputCode);
				return "BUTTON_UP";
			break;
			case 0xFF4AB5: //BUTTON_DOWN
				Serial.println("Constants: BUTTBUTTON_DOWNON_UP " + inputCode);
				return "BUTTON_DOWN";
			break;
			case 0xFF10EF: //BUTTON_LEFT
				Serial.println("Constants: BUTTON_LEFT " + inputCode);
				return "BUTTON_LEFT";
			break;
			case 0xFF5AA5: //BUTTON_RIGHT
				Serial.println("Constants: BUTTON_RIGHT " + inputCode);
				return "BUTTON_RIGHT";
			break;
			default: //error
				Serial.println("Constants: unknown button " + inputCode);
				return "error_code";
			break;
		}
}
void Constants::setup() {
}
#endif