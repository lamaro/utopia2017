#include "Arduino.h"
#include "pinDefinition.h"
int xv = 0;
int yv = 0;
int medx = 0;
int medy = 0;
int maxx = 0;
int maxy = 0;
int m1 = 0;
int m2 = 0;
int m3 = 0;
int m4 = 0;
int rwheel = 0;
int lwheel = 0;

int slow = 250;
int med = 400;
int full = 1000;

void steerSetup()
{
  // Set pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(xjoy, INPUT);
  pinMode(yjoy, INPUT);
  pinMode(A2, INPUT_PULLUP);
  delay(1000); // dice el manual sobre usar analog como input.
  medx = analogRead(xjoy); // el joystick por default está en el medio
  medy = analogRead(yjoy);
  maxx = medx * 2;
  maxy = medy * 2;
}

void motors(int m1, int m2)
{
  lwheel = m1; // (-yv + xv);
  rwheel = m2; // (-yv - xv);
}

// (-Y + X) / 1000.0
// (-Y - X) / 1000.0
void joy()
{
  xv = constrain(map(analogRead(xjoy), 0, maxx, -1000, 1000), -1000, 1000);
  yv = constrain(map(analogRead(yjoy), 0, maxy, 1000, -1000), -1000, 1000);
  motors(-yv + xv, -yv - xv); // diferencial
}

// ----------------------------------------
// control del robot.
// ----------------------------------------
void drive(int fb, int lr)
{
  xv = lr;
  yv = -fb;
  motors(-yv + xv, -yv - xv); // diferencial
}

void rotate(int turn, int speed){
  motors(turn * speed, turn * -speed);
}

void stop(){
  drive(0,0);
}

// ----------------------------------------


void run()
{
  m1 = map(lwheel, -1000, 1000, 0, 255);
  m2 = map(lwheel, -1000, 1000, 255, 0);
  m3 = map(rwheel, -1000, 1000, 0, 255);
  m4 = map(rwheel, -1000, 1000, 255, 0);
  // Serial.print(m1);
  // Serial.print('\t');
  // Serial.print(m2);
  // Serial.print('\t');
  // Serial.print(m3);
  // Serial.print('\t');
  // Serial.print(m4);
  // Serial.print('\n');
  analogWrite(motorPin1, m1);
  analogWrite(motorPin2, m2);
  analogWrite(motorPin3, m3);
  analogWrite(motorPin4, m4);
}

void testSequence2()
{
  drive(1000, 0);
  run();
  delay(2000);
  drive(-1000, 0);
  run();
  delay(2000);
  drive(-500, 500);
  run();
  delay(2000);
  drive(-500, -500);
  run();
  delay(2000);
  drive(0, 0);
  run();
}

void testSequence()
{
  // Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
  // This code  will turn Motor A clockwise for 2 sec.
  analogWrite(motorPin1, 180);
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 180);
  analogWrite(motorPin4, 0);
  delay(5000);
  // This code will turn Motor A counter-clockwise for 2 sec.
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 180);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4, 180);
  delay(5000);
  // This code will turn Motor B clockwise for 2 sec.
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 180);
  analogWrite(motorPin3, 180);
  analogWrite(motorPin4, 0);
  delay(1000);
  // This code will turn Motor B counter-clockwise for 2 sec.
  analogWrite(motorPin1, 180);
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4, 180);
  delay(1000);
  // And this code will stop motors
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4, 0);
}

