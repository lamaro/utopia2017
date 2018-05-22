#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#include "pinDefinition.h"
#endif


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDS_PIN, NEO_GRB + NEO_KHZ800);






void downloadSetup() {
  // put your setup code here, to run once:
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(BUZZER, HIGH); // pongo el pin en alto porque el buzzer esta conectado a 5V.
  pixels.begin(); // This initializes the NeoPixel library.
  // Serial.begin(115200);
}


// funciones de los leds

int ledsbuffer[NUMPIXELS];
unsigned long pLedUpdate = 0;        // will store last time LED was updated
unsigned int currentLed = 0;
int delayVal = 120;
int dir = 1;

void playKit() {
  if ((millis() - pLedUpdate) >= delayVal) {
    pLedUpdate = millis();
    currentLed = (currentLed + dir);
    dir = currentLed > 0 & currentLed < (NUMPIXELS - 1) ? dir : dir * -1;  // ida y vuelta
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    if (i == currentLed) {
      ledsbuffer[i] = 120;
    } else {
//      Serial.println(ledsbuffer[i]);
      ledsbuffer[i] = constrain(ledsbuffer[i] - 10, 0, 255);;

    }
    pixels.setPixelColor(i, pixels.Color(ledsbuffer[i], ledsbuffer[i], ledsbuffer[i])); // Moderately bright green color.

  }
  pixels.show(); // This sends the updated pixel color to the hardware.

}

boolean showEmpty()
{
  currentLed = 0;
  dir = 1;
  
  for (int i = 0; i < NUMPIXELS; i++) {
    ledsbuffer[i] = 0;
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Moderately bright green color.
  }
  pixels.show();
  return true;
}

void reset(){
  currentLed = 0;
  dir = 1;
  for (int i = 0; i < NUMPIXELS; i++) {
    ledsbuffer[i] = 0;
    pixels.setPixelColor(i, pixels.Color(ledsbuffer[i], ledsbuffer[i],ledsbuffer[i])); // Moderately bright green color.
  }
  pixels.show();
}

void silence()
{
  noTone(BUZZER);
  digitalWrite(BUZZER, HIGH); // pongo el pin en alto porque el buzzer esta conectado a 5V.
}

boolean ledsReseted = false;
unsigned long downloadingSpeed = 2E3;

boolean playDownloading(unsigned long currentTime) {
  if(!ledsReseted){
    ledsReseted = showEmpty();
    Serial.println("reseting leds");
  }else{
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i == currentLed) {  
        pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Moderately bright green color.
      }      
    }
    pixels.show(); // This sends the updated pixel color to the hardware.

    if ((currentTime - pLedUpdate) >= downloadingSpeed) {
      pLedUpdate = currentTime;
      currentLed ++;            
      if(currentLed >= NUMPIXELS){        
        action = WAITING;
        ledsReseted = false;
        reset();
        silence();
        // nextUpdate = currentTime + 5E3;
        delay(1000);
        return true;
      }
    }
  }
  return false;
}

int fadevalue = 0;
int fadetime = 20;
int fadedir = 1;

void playInout(unsigned long currentTime)
{
    for (int i = 0; i < NUMPIXELS; i++) {     
        pixels.setPixelColor(i, pixels.Color(fadevalue, fadevalue, fadevalue)); // Moderately bright green color.
    }

    pixels.show(); // This sends the updated pixel color to the hardware.

    if ((currentTime - pLedUpdate) >= fadetime) {
      fadevalue = constrain(fadevalue + 16 * fadedir, 0, 255);
      fadedir = fadevalue <= 0 | fadevalue >= 255 ? fadedir * -1 : fadedir; 
    }

}


// funciones del sonido.
// SONIDO

unsigned long previousOn = 0;        // will store last time LED was updated
unsigned long onInterval = 1000;
unsigned long previousOff = 0;
unsigned long offInterval = 1000;

void playSound() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousOn >= onInterval) {
    onInterval = random(100);
    previousOn = currentMillis;
    tone(BUZZER, random(1000, 4000));
  }

  if (currentMillis - previousOff >= offInterval) {
    offInterval = 20 + random(1500);
    previousOff = currentMillis;
    tone(BUZZER, random(1000, 4000));
  }

}





