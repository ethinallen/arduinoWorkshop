#define BUTTON_PIN 8

void setup() {
  Serial.begin(9600);                                        
  pinMode(BUTTON_PIN, INPUT);                                         
  pinMode(13, OUTPUT); //Use 13 because it has an LED built into the Arduino Uno board

} 


void loop () {
  
  //Read the button value and "print" it to the serial monitor
  byte buttonValue = digitalRead(BUTTON_PIN);
  //byte buttonValue = analogRead(0);
  Serial.println(buttonValue);

  //Change the LED
  if(buttonValue > 0)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);

  //Wait a bit 
  delay(200);
  
} 
