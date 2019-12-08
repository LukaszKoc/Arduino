/****************************************************************************************
* digital i/o pin assignment
*
* this uses the undocumented feature of Arduino - pins 14-19 correspond to analog 0-5
****************************************************************************************/
//if pin is LOW on boot then robot will connect to wifi otherwise will create AccessPoint 
#define ACCESS_POINT_PINT 17 //SD3

//MOTOR 
#define MOTOR_R_TURN_1_PIN D1
#define MOTOR_R_TURN_2_PIN D2
	//HALL
	#define MOTOR_R_HYALL_1_PIN D6
	#define MOTOR_R_HYALL_2_PIN D7
//MOTOR 2
#define MOTOR_L_TURN_1_PIN D3
#define MOTOR_L_TURN_2_PIN D4
	//HALL
	#define MOTOR_L_HYALL_1_PIN D3
	#define MOTOR_L_HYALL_2_PIN D4
