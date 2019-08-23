
/****************************************************************************************
* digital i/o pin assignment
*
* this uses the undocumented feature of Arduino - pins 14-19 correspond to analog 0-5
****************************************************************************************/

//DisplayController
#define LCD_rs 12
#define LCD_en 11
#define LCD_d7 7
#define LCD_d6 6
#define LCD_d5 5
#define LCD_d4 4

//IRController
#define IR_RECV_PIN 3

//JOISTICKController
#define JS_X_pin 0 // analog pin connected to X output
#define JS_Y_pin 1 // analog pin connected to Y output
#define JS_SW_pin 2 // digital pin connected to switch output
 
//ServoController
#define SERVO_INPUT 9
