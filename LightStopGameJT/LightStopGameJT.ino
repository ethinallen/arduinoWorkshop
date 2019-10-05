// FastLED Setup
#include <FastLED.h>
#define NUM_LEDS 40
#define DATA_PIN 5
#define BUTTON_PIN 8
#define MOVINGSPOT CRGB(0,0,255);
CRGB leds[NUM_LEDS];

volatile boolean waitingForButton = true;
bool dotDirection = 1;
byte globalBright = 120; //The max brightness for the strip
byte levelSpeeds[] = {170,130,115,100,90,80,70,60,50,40,30,25,20,15,12,10,9,5,1};
byte numLevels = 20;
byte currentLevel = 0;
byte gameMode = 1;
byte stopPosition, originalGameMode, failureMode, currentHue;
byte dullValue = 80; //The brightness of the dull amount
int currentSpot;
unsigned long restTime, loopStart, restTimeout;

void setup() {
  //FastLED setup
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setCorrection(TypicalLEDStrip);
	FastLED.setMaxPowerInVoltsAndMilliamps(5,400);
	FastLED.setBrightness(globalBright);
	
  

  //Initialize digital inputs/outputs 
   pinMode(BUTTON_PIN,INPUT);

  //Start Serial port at 9600 baud rate
   Serial.begin(9600);

   /*Game mode
    1 = scroll across
    2 = bounce
    3 = unpredictable
   */
   gameMode = 3;

   /*Failure mode
    * 1 = go down by 1 level
    * 2 = reset to level 0
    */
   failureMode = 1;

   
   originalGameMode = gameMode;//Necessary for the unpredictable game mode
   randomSeed(analogRead(0));  //Make random things be more random
   fill_solid(leds,NUM_LEDS, CRGB::Black); //Turn off all the lights
}

void loop() {
  
  waitingForButton = true;
  //Set strip to a nice dull color in the color spectrum
  currentHue = map(currentLevel,0,numLevels,0,255);
  fill_solid(leds,NUM_LEDS,CHSV( currentHue, 255, dullValue));

  //Determine the stop position and set it to bright white
  byte testStopPosition = -1; //Temporary variable for comparing the newly generated value to the old one 
  /*
   * Make sure it isn't within a few lights of either end of the string
   * Make sure it is a different number than before by at least 2 pixels 
   */
  while(testStopPosition < 8 || (testStopPosition > (NUM_LEDS-7)) || testStopPosition == stopPosition || (testStopPosition<stopPosition+2 && testStopPosition > stopPosition-2))
  {
    testStopPosition = random(NUM_LEDS);
  }
  stopPosition = testStopPosition;
  leds[stopPosition] = CRGB(255,255,255);
  FastLED.show();
  
  Serial.print("Current level:  ");
  Serial.println(currentLevel);
  
  if(originalGameMode == 3) gameMode=random(1,3);
  
  //Run a single light down the strip until the button is pressed
  while(waitingForButton)
  {
    if(gameMode == 1)
      {currentSpot++;
      leds[currentSpot-1] = CHSV( currentHue, 255, dullValue); //Fill the previous spot with the dull color it should be
      if(currentSpot >= NUM_LEDS) currentSpot = 0;
      }
    else if (gameMode == 2)
      {if(dotDirection == 1) //Going from beginning of strip to end
        {currentSpot++;
        leds[currentSpot-1] = CHSV( currentHue, 255, dullValue);
        if(currentSpot >= NUM_LEDS) {
          currentSpot-=2;
          dotDirection = 0;
          }
        }
      else                  //Going from end of strip to beginning
        {currentSpot--;
        leds[currentSpot+1] = CHSV( currentHue, 255, dullValue); 
        if(currentSpot <0) {
          currentSpot+=2;
          dotDirection = 1;
          }
        }
      }
    leds[currentSpot] = MOVINGSPOT; //Set it to whatever the moving spot should look like
    leds[stopPosition] = CRGB(255,255,255);//Set this back to the right color in case we overwrote it
    FastLED.show();
    
    //Delay a certain time based on level while also looking for a button press
    loopStart = millis();
    restTime = levelSpeeds[currentLevel]; //Change how long we're waiting based on the level
    bool buttonAnimate = true;
    bool buttonPressed = 0;
    restTimeout = 0;
    while(buttonAnimate)
    {
      restTimeout = millis() - loopStart;
      if(digitalRead(BUTTON_PIN)==1) //Check if the button was pressed 
        { buttonPressed = 1;
          buttonAnimate = false; 
        }
      if(restTimeout>=restTime)  break;
    }
    
    if(buttonPressed)
    {
      waitingForButton = false;
      bool correctSpot = false;
      if(currentSpot == stopPosition)   //Check if it was in the winning spot or not
        correctSpot = true;
      
      //WIN
      if(correctSpot)
      {
        Serial.println("Congrats!! You did the thing!!");
        leds[currentSpot] = CRGB(0,255,0);  //Set the spot you stopped on to green for good
        FastLED.show();
        delay(1000);
        if(currentLevel < numLevels-1) currentLevel++; //Increase current level
      }
      
      //LOSE
      else
      {
       Serial.println("FAILURE") ;
        leds[currentSpot] = CRGB(255,0,0);  //Set the spot you stopped to just red because bad
        FastLED.show();
        delay(650);
        explodeRed(); //Play a fun explode animation 
        //Reset or reduce level
        if(failureMode == 1)
          if(currentLevel>0) currentLevel-=1;
        else if (failureMode == 2)
          currentLevel = 0;
        
        
      }
    }
    else //Button was not pressed
    {
      
    }
  }
}
