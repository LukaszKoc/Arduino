 
#ifndef BuzzController_h
#define BuzzController_h 

class BuzzController {
  private:
    int buzzPin;
  public:
    void setup();
    int buzz(int toneHz);
    int stop();
    BuzzController(int buzzPin_arg) {
      buzzPin = buzzPin_arg;
    }
}; 

void BuzzController::setup() {
      pinMode(buzzPin, OUTPUT);
}

int BuzzController::buzz(int toneHz = 1000) {
  tone(buzzPin, toneHz); // Send 1KHz sound signal...
} 
int BuzzController::stop() {
    noTone(buzzPin);     // Stop sound...
}

#endif