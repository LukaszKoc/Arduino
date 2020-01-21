#ifndef ArduinoUtil_h
#define ArduinoUtil_h 

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  3        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

void wait(int timeout = 500) {
	delay(timeout);
	Serial.print(".");
}


void deepSleep(int wakeUpTimeout = TIME_TO_SLEEP) {
	esp_sleep_enable_timer_wakeup(wakeUpTimeout * uS_TO_S_FACTOR);
	esp_deep_sleep_start();
}



#endif