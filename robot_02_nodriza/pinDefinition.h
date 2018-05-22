#include "Arduino.h"

#ifndef _PIN_DEFS_
#define _PIN_DEFS_

// PWM en mega del 0 al 13, 44, 45 y 46
// Motor A
const int motorPin1 = 9; // Pin 14 of L293
const int motorPin2 = 10; // Pin 10 of L293
// Motor B
const int motorPin3 = 6; // Pin  7 of L293
const int motorPin4 = 5; // Pin  2 of L293

const int BUZZER   = 12;
const int LEDS_PIN  = 7;

const int LCD_D4  = 22; // Violeta
const int LCD_D5  = 24; // Gris
const int LCD_D6  = 26; // Blanco
const int LCD_D7  = 28; // Negro
const int LCD_RS  = 30; // Verde
const int LCD_EN  = 32; // Azul


const int dataPin = 2; // the number of the pushbutton pin


#define NUMPIXELS      8



const int SERIAL_1_RX = 19; // mal rotulado en mi placa mega

const int xjoy = A1;
const int yjoy = A0;
// SENSORES SEGUIDOR DE LINEA 
// los sensores estan definidos viendo al robot desde arriba
// L1 L2 -- -- R2 R1
const int CNY_R1 = A4;
const int CNY_R2 = A5;
const int CNY_L2 = A6;
const int CNY_L1 = A7;




#endif

