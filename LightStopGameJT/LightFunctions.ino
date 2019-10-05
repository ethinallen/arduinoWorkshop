void fadeRed(int fadeTime) {
  unsigned long firstMillis = millis();
  while(millis() < firstMillis+fadeTime)
  {
  uint8_t fadeval = beatsin8(12,2,20);
  fadeToBlackBy(leds, NUM_LEDS, fadeval); 
  leds[millis()/20%NUM_LEDS] = CHSV(0,255,255); 
  FastLED.show();
  }
}

void explodeRed()
{

    //for(int i = currentSpot; i < NUM_LEDS; i++)
    
    int i = currentSpot+3;
    int j = currentSpot-3;
    while(i < NUM_LEDS || j > 0)
      {
        if(i < NUM_LEDS)
        {
          leds[i] = CRGB(255,0,0);
          if(i-6>currentSpot) {
            leds[i-2].fadeToBlackBy(64);
            leds[i-3].fadeToBlackBy(64);
            leds[i-4].fadeToBlackBy(64);
            leds[i-5].fadeToBlackBy(64);
            leds[i-6] = CHSV( currentHue, 255, dullValue);
          }
        }
        if(j > 0)
        {
          leds[j] = CRGB(255,0,0);
          if(j+6<currentSpot) {
            leds[j+2].fadeToBlackBy(64);
            leds[j+3].fadeToBlackBy(64);
            leds[j+4].fadeToBlackBy(64);
            leds[j+5].fadeToBlackBy(64);
            leds[j+6]= CHSV( currentHue, 255, dullValue);
          }
        }
      i++;
      j--;
      FastLED.show();
      delay(30);
    }
  
  
}
