#include "Arduino.h"
#include "pinDefinition.h"


int sensors[] = {CNY_L1, CNY_L2, CNY_R2, CNY_R1};
int blackValue[sizeof(sensors)/sizeof(int)];
int sensorsValue[sizeof(sensors)/sizeof(int)];
byte status = 0;
int treshold = 32;

// const unsigned long factor = 8;
float factor = 0.85;
int ease(float current, float prev, float factor)
{
	return (unsigned int) (prev * factor) + (current * (1 - factor));
}

void calibrateSensors(){
	delay(100);
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++) {
		blackValue[i] = analogRead(sensors[i]);		
		delay(10);
	}
}

void lineFollowerSetup()
{
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++) pinMode(sensors[i], INPUT);
	calibrateSensors();
}



void readSensors()
{
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++) {
		sensorsValue[i] = ease(analogRead(sensors[i]), sensorsValue[i], factor);		
		Serial.print(sensorsValue[i]);
		Serial.print("\t");
	}	

	Serial.println();
}

void updateSensors(){
	status = 0;
	// Serial.print('R');
	for(int i = 0; i < sizeof(sensors)/sizeof(int); i++){
		byte value = sensorsValue[i] > (blackValue[i] * 2) ? 1 : 0; // 0 estoy en la linea, 1 me sali		
		status |= value << i;
		// Serial.print(value & B00000001);
	}	
	// Serial.print('L');
	// Serial.println();
	
	
}

