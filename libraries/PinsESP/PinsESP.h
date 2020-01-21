#ifdef ESP32
	#define SOID_MOISTURE_A_BURO 36
	#define SOID_MOISTURE_A_MINT 39
	#define SOID_MOISTURE_A_ALOES 34
	#define SOID_MOISTURE_A_PLANT_1 14
	#define SOID_MOISTURE_A_PLANT_2 12
	#define DHT_PIN_D 33
	#define BLUE_LED_D GPIO_NUM_2
#elif defined(ESP8266)
	#define DHT_PIN_D D6
	#define SOID_MOISTURE_D D7
	#define SOID_MOISTURE_A D8

	#define ACCESS_POINT_PINT 17 

	#define NODEMCU_ENV 1
	#define RX_PIN D6
	#define TX_PIN D5
	//MOTOR 
	#define MOTOR_R_TURN_1_PIN D5
	#define MOTOR_R_TURN_2_PIN D6
	// MOTOR 2
	#define MOTOR_L_TURN_1_PIN D7
	#define MOTOR_L_TURN_2_PIN D8
#else
	#error Platform not supported
#endif
