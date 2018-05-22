#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define BUZZER 12
#define PIN    6
#define NUMPIXELS      8

int frameRate = 20;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define GO            1
#define DOWNLOADING   2
#define WAITING       4

int action = GO;

unsigned long nextUpdate = 3E3;
unsigned long timeout = 3E3;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(BUZZER, HIGH); // pongo el pin en alto porque el buzzer esta conectado a 5V.
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(115200);
}

unsigned long pFrameTime = 0;        //

void loop() {
  unsigned long currentTime = millis();
  
//  if (currentTime >= nextUpdate) {
//    nextUpdate = currentTime + timeout; // set up the next timeout period
//    action = action == GO ? DOWNLOADING : GO;
//  }
  
  
  if ((currentTime - pFrameTime) >= frameRate) {
    pFrameTime = currentTime;
    switch (action) {
      case GO:
        {
          if (currentTime >= nextUpdate) {
             nextUpdate = currentTime + timeout; // set up the next timeout period
             action = action == GO ? DOWNLOADING : GO;
          }
          
          playKit();
          silence();
          break;
        }

        case DOWNLOADING:
        {
          playSound();
          playDownloading(currentTime);

          break;
        }

        case WAITING:
        {

          break;
        }
    }
  }
}


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

boolean ledsReseted = false;
unsigned long downloadingSpeed = 2E3;

void playDownloading(unsigned long currentTime) {
  if(!ledsReseted){
    ledsReseted = showEmpty();
    Serial.println("reseting leds");
  }else{
//    Serial.println("leds Reseted");
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i == currentLed) {  
        pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Moderately bright green color.
      }      
    }
    
    if ((currentTime - pLedUpdate) >= downloadingSpeed) {
      pLedUpdate = currentTime;
      currentLed ++;            
      if(currentLed > NUMPIXELS){        
        action = WAITING;
        ledsReseted = false;
        reset();
        silence();
        nextUpdate = currentTime + 5E3;
      }
    }
    
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
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

void silence()
{
  noTone(BUZZER);
  digitalWrite(BUZZER, HIGH); // pongo el pin en alto porque el buzzer esta conectado a 5V.
}


