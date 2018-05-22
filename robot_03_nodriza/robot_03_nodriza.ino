#include "pinDefinition.h"
#include "steer.h"
#include "lineFollower.h"
//#include "leds.h"
// estados de control general del robot
#define GO 1 // el robot avanza - usa el lineFollower
#define DOWNLOADING 2
#define WAITING 4
#define TURN 8
#define BACKWARDS 16
int action = GO;
unsigned long pFrameTime = 0; //
int frameRate = 20;
const int INV = B11111111;
void setup()
{
	Serial.begin(9600);
	Serial1.begin(600);
	delay(3000);
	lineFollowerSetup();
	steerSetup();
	// lcdSetup();
	//downloadSetup();
	// pinMode(dataPin, INPUT);
	// attachInterrupt(0, interr, FALLING);
	//silence();
//	ledsOn();
testSequence();
//drive(0,-1000);
//run();
}

int direction = 1;
unsigned long lastDirectionChange;
unsigned long directionChangeTimeout = 1E3;
unsigned long turnDuration = 2E3;
unsigned long turnStartTime = 0;
unsigned long backwardsDuration = 1E3;
unsigned long backwardsStartTime = 0;
unsigned long downloadStartTime = 0;
unsigned long downloadDuration = 8 * 2E3;
void loop()
{
  
	// joy();
	// run();
	delay(1); // gano tiempo...
	// ------------------------------------
	unsigned long currentTime = millis();
	readSensors();
	updateSensors();
	// main loop
	if ((currentTime - pFrameTime) >= frameRate)
	{
		pFrameTime = currentTime; // controla las animaciones de las luces y demas
		switch (action)
		{
			case GO:
			{
				// lcdPrintCommand("ROBOT: GO");
//				playKit();


				wander(millis());
				if (detectBorder())
				{
					direction = inferDirection();
					backwardsStartTime = millis();
					action = BACKWARDS;
				}
				break;
			}
			case BACKWARDS:
				if (millis() - backwardsStartTime < backwardsDuration)
				{
					drive(slow, 0);
					run();
				}
				else
				{
					turnDuration = random(1E3, 4E3);
					turnStartTime = millis();
					action = TURN;
				}
				break;
			case TURN:
			{
				if (millis() - turnStartTime < turnDuration)
				{
					rotate(direction, med);
					run();
				}
				else
				{
					turnDuration = random(1E3, 4E3);
					// action = DOWNLOADING;
					action = random(0, 1E3) < 100 ? DOWNLOADING : GO;
					if(action == DOWNLOADING){
						drive(0,0);
						run();
						downloadStartTime = millis();
					 	for(int times = 0; times < 10; times ++){
					 		Serial1.println("DOWNLOADING");
					 		delay(10);
					 	} 					
					}
				}
				break;
			}
			case DOWNLOADING:
			{
				// lcdPrintCommand("ROBOT: DOWNLOADING");
//				playSound();
				// // playDownloading(currentTime);
	//			if(playDownloading(millis())){
		//			action = GO;	
	//				silence();
			//	}
				action = GO;
				break;
			}
		}
	}
}

const int W_WAIT = 0;
const int W_TURN = 1;
const int W_STEPS = 2;
const int W_GO = 4;
int wanderState = W_WAIT;
unsigned long p_wait_delay = 10E3; // ten secs
unsigned long p_turn_delay = 1E3;
unsigned long p_steps_delay = 1E3;
unsigned long p_event_time = 0;
int turnDirection = 1;
void wander(unsigned long currentTime)
{
	switch (wanderState)
	{
		case W_WAIT:
			drive(0, 0);
			run();
			
			if (currentTime - p_event_time > p_wait_delay)
			{
				p_event_time = currentTime;
				p_wait_delay = random(5E3, 20E3);
				wanderState = random(-1000, 1000) < 0? W_TURN:W_STEPS;
			}
			// do nothing
			break;
		case W_TURN:
			rotate(turnDirection, med);
			run();
			if (currentTime - p_event_time > p_turn_delay)
			{
				p_event_time = currentTime;
				p_turn_delay = random(1E3, 3E3);
				turnDirection = random(-1000, 1000) < 0? -1:1;
				wanderState = random(0, 1000) > 100? W_WAIT:W_STEPS;
			}
			break;
		case W_STEPS:
			drive(-slow, 0);
			run();
			if (currentTime - p_event_time > p_steps_delay)
			{
				p_event_time = currentTime;
				p_steps_delay = random(1E3, 3E3);
				wanderState = random(0, 1000) > 100? W_WAIT:W_TURN;
			}
			break;
		default:
			break;
			// do something
	}
}

boolean detectBorder()
{
	// return status != B00001111? true:false;
 
	return status != B00001001? true:false;
}

int inferDirection()
{
	return status == B00000011 || status == B00000001? -1:1; // trucho.
}

