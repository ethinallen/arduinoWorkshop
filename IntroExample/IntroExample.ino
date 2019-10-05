#define BUTTON_PIN 8

void setup() {

  Serial.begin(9600);                                        
  pinMode(BUTTON_PIN, INPUT);                                         
  pinMode(13, OUTPUT); //Use 13 because it has an LED built into the Arduino Uno board

} 


void loop () {
  
  //byte buttonValue = digitalRead(BUTTON_PIN);
  byte buttonValue = analogRead(0);
  Serial.println(buttonValue);
  delay(200);
  
} 
