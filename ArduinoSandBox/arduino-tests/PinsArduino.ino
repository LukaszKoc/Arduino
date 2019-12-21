/****************************************************************************************
* digital i/o pin assignment
*
* this uses the undocumented feature of Arduino - pins 14-19 correspond to analog 0-5
****************************************************************************************/
//if pin is LOW on boot then robot will connect to wifi otherwise will create AccessPoint 


#define AR2D2_BUZZER 9

// //MOTOR 
// #define MOTOR_R_TURN_1_PIN D1
// #define MOTOR_R_TURN_2_PIN D2
// 	//HALL
// 	#define MOTOR_R_HYALL_1_PIN D5
// 	#define MOTOR_R_HYALL_2_PIN D6
// //MOTOR 2
// #define MOTOR_L_TURN_1_PIN D3
// #define MOTOR_L_TURN_2_PIN D4
// 	//HALL
// 	#define MOTOR_L_HYALL_1_PIN D7
// 	#define MOTOR_L_HYALL_2_PIN D8
