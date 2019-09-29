#include <FastLED.h>
#define NUM_LEDS 10
#define DATA_PIN 5
#define button 8

CRGB leds[NUM_LEDS*3];
int light_speed = 500;
long stop_pos = 0;
int brightness = 100;

void setup() {
   FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
   pinMode(button,INPUT);

   for (int i = 0;i< NUM_LEDS*3;i++) {
    leds[i] = CRGB(0,0,0);
   }

}

void loop() {

  stop_pos = random(0,NUM_LEDS);
  leds[stop_pos] = CRGB(brightness,brightness,brightness);
  FastLED.show();

  for (int n = 0; n < 5;n++) {
    for (int i = 0;i < NUM_LEDS;i++) {
      if (stop_pos != i) {
        leds[i] = CRGB(brightness,brightness,0);
        FastLED.show();
        delay(light_speed);
        leds[i] = CRGB(0,0,0);
      } else {
        leds[i] = CRGB(0,brightness,0);
        FastLED.show();
        delay(light_speed);

         if ( digitalRead(button) == LOW) {
          win();
        }
        
        leds[i] = CRGB(brightness,brightness,brightness);
      }
    }
  
    for (int i = NUM_LEDS-2;i > 0 ;i--) {
      if (stop_pos != i) {
        leds[i] = CRGB(brightness,brightness,0);
        FastLED.show();
        delay(light_speed);        
        leds[i] = CRGB(0,0,0);
      } else {
        leds[i] = CRGB(0,brightness,0);
        FastLED.show();
        delay(light_speed);

        if ( digitalRead(button) == LOW) {
          win();
        }
        
        leds[i] = CRGB(brightness,brightness,brightness);
      }
    }
 }
 
 leds[stop_pos] = CRGB(0,0,0);
 
}


void all_on() {
  for (int i = NUM_LEDS-2;i > 0 ;i--) {
      leds[i] = CRGB(brightness,brightness,brightness);
    }
  FastLED.show();
}

void all_off() {
  for (int i = NUM_LEDS-2;i > 0 ;i--) {
      leds[i] = CRGB(0,0,0);
    }
  FastLED.show();
}

void win() {

  for (int n = 0;n<3;n++){
    for (int i = NUM_LEDS-2;i > 0 ;i--) {
        leds[i] = CRGB(brightness,0,0);
      }
    FastLED.show();
    delay(500);
    
    for (int i = NUM_LEDS-2;i > 0 ;i--) {
        leds[i] = CRGB(0,0,0);
      }
    FastLED.show();
    delay(500);
  }

  light_speed *= .5;
  stop_pos = random(0,NUM_LEDS);

}

  


