#define TRIGGER 12
#define ECHO 11
#define TIMEOUT 30000
#define WAITING_TIME 1000

long duration; 
double distance;
//The following code is run once at the start of execution to setup the different peripherals

void setup() 
{ 
  pinMode(TRIGGER, OUTPUT); 
  digitalWrite(TRIGGER, LOW); 
  pinMode(ECHO, INPUT); 
  
  // Set up the serial Communication
  //Serial.begin(9600); 
}
void loop() 
{ 
  //The following code is run repeatedly 
  digitalWrite(TRIGGER, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIGGER, LOW); 
  delayMicroseconds(10); 
  
  duration = pulseIn(ECHO, HIGH, TIMEOUT); 
  // Calculate the distance base on the duration
  distance = (duration/2.0);
  //Serial.print("Duration: ");
  //Serial.print(duration); 
  //Serial.println(" microseconds"); 
  
  delay(WAITING_TIME); 
}
