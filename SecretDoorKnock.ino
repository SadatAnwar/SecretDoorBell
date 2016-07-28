/*
Code to detect the secret bell ring and then open the door
*/
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int doorSignal= 12;
int doorBell=  A0;
unsigned long period = 5000; //time to read pattern

// the setup routine runs once when you press reset:
void setup() {     
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);  //Switch off the annoying light on the board, maybe even save some battery
  // initialize the digital pin as an output.
  pinMode(doorSignal, OUTPUT); 
  pinMode(doorBell, INPUT);  
  digitalWrite(doorSignal, HIGH); 
  Serial.begin(9600);  //debug
}

// the loop routine runs over and over again forever:
void loop() {
  //read the value on input
  if(analogRead(doorBell)>250){
    delay(500);
     if(ringPassword()){
        openDoor();
     }
  }
}

//Method to match pattern
boolean ringPassword(){
  // Initialize a start time variable
  int bellCount = 0;
  unsigned long startTime = millis();
  unsigned long currentTime = millis();
  while((unsigned long)(currentTime-startTime) < period){
    if(analogRead(doorBell)>250) {
      while(analogRead(doorBell)>0){ //Loop to hold the state, long press is still one ping
      }
      bellCount= bellCount+1;
    }
    currentTime = millis();
  }
  if(bellCount==3){
    return true;
  }
    return false;
}
  

void openDoor(){
  //code to open door
  //send LOW to relay to complete the opendoor circuit
  digitalWrite(doorSignal,LOW);
  delay(800);
  digitalWrite(doorSignal,HIGH);
  
}

boolean ringDetect(){
  int sensorVal = analogRead(doorBell);
  if(sensorVal >250){
    Serial.println(sensorVal);
    Serial.println("Ring detected");
    return true;    
  }
  else
  return false;
}
//master1
