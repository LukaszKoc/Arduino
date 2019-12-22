#ifndef R2D2Controller_h
#define R2D2Controller_h 
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

class R2D2Controller {
  private:
    int volume = 306;
    int buzzerPin;
    int counter = 0; 
    void secondSection();
    void firstSection();
    void beep(int note, int duration);
  public:
    R2D2Controller(int buzer_pin) {
      buzzerPin = buzer_pin;
    }
    void imperialMarch();
    void r2D2_tell();
    void r2D2_rand();
    void setup () {
      pinMode(buzzerPin, OUTPUT); // Digital Pin 9
    }
}; 

void R2D2Controller::r2D2_rand() {
  int r2d2Tones[] = {
    3520, 3136, 2637, 2093, 2349, 3951, 2794,4186
  };
  for (int notePlay = 0; notePlay < 8; notePlay++) {
    int noteRandom = random(7);
    //vol.tone(buzzerPin,r2d2Tones[noteRandom], volume);
    tone(buzzerPin, r2d2Tones[noteRandom]);
    delay(95);
    noTone(8);
  }
}

void R2D2Controller::r2D2_tell() {
    tone(buzzerPin, 3520, 80); noTone(8);
    tone(buzzerPin, 3136, 80); noTone(8);
    tone(buzzerPin, 2637, 80); noTone(8);
    tone(buzzerPin, 2093, 80); noTone(8);
    tone(buzzerPin, 2349, 80); noTone(8);
    tone(buzzerPin, 3951, 80); noTone(8);
    tone(buzzerPin, 2794, 80); noTone(8);
    tone(buzzerPin, 4186, 80); noTone(8);
}

void R2D2Controller::imperialMarch() {
  firstSection();
  //Play second section
  secondSection();
  //Variant 1
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 350);  
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);  
  beep(cH, 125);
  beep(eH, 650);
 
  delay(500);
 
  //Repeat second section
  secondSection();
 
  //Variant 2
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  
 
  delay(650);
}


void R2D2Controller::beep(int note, int duration){
  // vol.tone(buzzerPin,note, volume*1.5);
  tone(buzzerPin, note, duration);
  delay(duration);
  noTone(50);
  counter++;
}
 
void R2D2Controller::firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
 
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
}
 
void R2D2Controller::secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
 
  delay(325);
 
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
 
  delay(350);
}

#endif