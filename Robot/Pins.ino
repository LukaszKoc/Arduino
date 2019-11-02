
/****************************************************************************************
* digital i/o pin assignment
*
* this uses the undocumented feature of Arduino - pins 14-19 correspond to analog 0-5
****************************************************************************************/

//DistanceReaderController
#define BAT_TRIG_PIN 12
#define BAT_ECHO_PIN 11

//Buzzer
#define BUZZER_PIN 4

//DisplayController
#define LCD_RS_PIN 12
#define LCD_EN_PIN 11
#define LCD_D7_PIN 7
#define LCD_D6_PIN 6
#define LCD_D5_PIN 5
#define LCD_D4_PIN 4

//IRController
#define IR_RECV_PIN 3

//JOISTICKController
#define JS_X_A_PIN 2 // analog pin connected to X output
#define JS_Y_A_PIN 3 // analog pin connected to Y output
#define JS_SW_PIN  4// digital pin connected to switch output
 
//ServoController
#define SERVO_INPUT 9


//MOTOR 
#define MOTOR_1_SPREED_A_PIN 10
#define MOTOR_1_TURN_1_PIN 9
#define MOTOR_1_TURN_2_PIN 8 
//MOTOR 2
#define MOTOR_2_SPREED_A_PIN 5
#define MOTOR_2_TURN_1_PIN 6
#define MOTOR_2_TURN_2_PIN 7