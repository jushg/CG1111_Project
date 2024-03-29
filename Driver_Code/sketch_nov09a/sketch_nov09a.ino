#include <MeMCore.h>
#include "Wire.h"
#define THRESHOLD0 2.85
#define THRESHOLD1 1.9
#define WALLL 2
#define WALLR 0.5
#define LEFT A1
#define RIGHT A0

#include <SoftwareSerial.h>
 
MeLineFollower lineFinder(PORT_1);
MeUltrasonicSensor ultraSensor(PORT_3);
MeRGBLed led(0, 30);
MeLightSensor lightSensor(PORT_8);
MeBuzzer buzzer;
MeDCMotor motor1(M1); //left motor
MeDCMotor motor2(M2); //right motor
MeInfraredReceiver infraredReceiverDecode(PORT_4);

#define RGBWait 200 //in milliseconds
#define LDRWait 10 //in milliseconds 

#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define PURPLE 5
#define BLACK 6
#define NEAR_WALL 6 //for two cases the value may need to be changed
int i = 150; // analog value to control speed of motor
bool finished = false;

// Music notes
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int melody[] = {
  NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_FS4,
  NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_G4,
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_CS5, NOTE_D5, NOTE_A4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_CS4,
  0
};

// note durations: 4 = quarter note, 8 = eighth note, etc
int noteDurations[] = {
  2, 2, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 2
};
int melody2[] = {
  NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_F4,
  NOTE_G4, NOTE_G4, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_G4, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4, NOTE_G4, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,

  NOTE_G4, NOTE_D2, NOTE_G4, NOTE_D5, NOTE_C5, NOTE_D2, NOTE_AS4,NOTE_D2, NOTE_A4,NOTE_F2, NOTE_A4, NOTE_AS4, NOTE_C5,NOTE_F2, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_D2, NOTE_G4, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4, NOTE_D2, NOTE_G4, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
};

// note durations: 4 = quarter note, 8 = eighth note, etc
int noteDurations2[] = {
  8, 8, 8, 8,
  4, 8, 8, 4, 4, 4, 8, 8, 4, 8, 8,
  4, 8, 8, 8, 8, 8, 8,
  4, 8, 8, 8, 8, 8, 8,
  
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
};
void play_victory(){  
  long length = 40;
  for(long j = 0; j < 2; j += 1){
    for (long i = 0; i < length; i += 1){
      buzzer.tone(melody2[i], 1000 / noteDurations2[i] );
      delay(100);  
    }
  }
}

void moveForward (int speed_i = 150);

void setup() 
{
  double left;
  double right;
  infraredReceiverDecode.begin();
  Serial.begin(9600);
  // put your setup code here, to run once:
  led.setpin(13);
  //running through the maze
  
  while (!finished) 
  {
    if (front_near_wall() || find_black_line()) 
    {
      stop();
      checkColor();
    } 
    else 
    {
      moveForward(190);
      left = analogRead(LEFT) / 1023.0 * 5;
      right = analogRead(RIGHT) / 1023.0 *5;
      if (left > THRESHOLD0 && right > THRESHOLD1) {
        moveForward(190);
      } else {
        if (left <= THRESHOLD0 && left > WALLL) {
        Serial.println("close left");
          adjustRight();
        }
        else if (right <= THRESHOLD1 && right > WALLR) {
        Serial.println("Close right");
          adjustLeft();
        }
      
      else if (right < WALLR) {
        moveBackward();
        delay(500);
        motor1.run(i);
        motor2.run(i);
        delay(50);
        moveForward();
      }
      else if (left < WALLL) {
        moveBackward();
        delay(500);
        motor1.run(-i);
        motor2.run(-i);
        delay(50);
        moveForward();
      }
      }
    }
  }
}

void loop() {
   /*double left = analogRead(LEFT) / 1023.0 * 5;
      double right = analogRead(RIGHT) / 1023.0 *5;
      Serial.println(left);
      Serial.print(" , ");
      Serial.println(right);*/
}
//decide 
void checkColor()
{
  long thecolor = getColor();
  if(thecolor == RED) 
  {
    //turn left
    turnLeft();
  }
  else if(thecolor == GREEN) 
  {
    //turn right
    turnRight();
  }
  else if(thecolor == YELLOW) 
  {
    // 180 degree in a same grid
    UTurn();
  }
  else if(thecolor == PURPLE) 
  {
    // two successive left turns
    doubleLeft();
  }
  else if(thecolor == BLUE) 
  {
    //two successive right turns
    doubleRight();
  }
  else if(thecolor == BLACK)
 {
     //finished, play song
   
    play_victory();
    //finished
    finished = true;
    
  }
}
void moveForward(int speed_i)
{
  motor1.run(-speed_i);
  motor2.run(speed_i );
}

void moveBackward()
{
  motor1.run(i);
  motor2.run(-i);
}

void stop()
{
  motor1.stop();
  motor2.stop();
}

void turnLeft()
{
  motor1.run(i);
  motor2.run(i);
  delay(430);
  stop();
}

void turnRight()
{
  motor1.run(-i);
  motor2.run(-i);
  delay(430);
  stop();
}

void UTurn()
{
  double left = analogRead(LEFT) / 1023.0 * 5;
  double right = analogRead(RIGHT) / 1023.0 *5;
  if (left >= THRESHOLD0 ) {
    turnLeft();
    stop();
    turnLeft();
  }
  else {
    turnRight();
    stop();
    turnRight();
  }
}

void doubleLeft()
{
  turnLeft();
  while(!front_near_wall())
  {
    moveForward();
  }
  stop();
  turnLeft();
}
void doubleRight()
{
  turnRight();
  while(!front_near_wall())
  {
    moveForward();
  }
  stop();
  turnRight();
}

void adjustLeft() // to be used if mbot is not moving straight based on data from the ir sensors
{
 //double v = analogRead(RIGHT) / 1023.0 * 5;
  //if (v < THRESHOLD1) {
    motor1.run(-i);
    motor2.run(i+15);
    delay(70);
    motor1.run(-i);
    motor2.run(i);

}
void adjustRight() // to be used if mbot is not moving straight based on data from the ir sensors
{
 //double v = analogRead(LEFT) / 1023.0 * 5;
  //if (v < THRESHOLD0) {
    motor1.run(-i-15);
    motor2.run(i);
    delay(70);
    motor1.run(-i);
    motor2.run(i);

  //}
}

bool front_near_wall() 
{
  double distance = ultraSensor.distanceCm();
  return (distance < NEAR_WALL);
}

bool find_black_line() 
{
  int sensorState = lineFinder.readSensors();
  return (sensorState == S1_IN_S2_IN); 
}

uint16_t getAvgReading(int times){      
//find the average reading for the requested number of times of scanning LDR
  uint16_t reading;
  uint16_t total =0;
  for(int i = 0;i < times;i++){
    reading = lightSensor.read();  // to change to lightsencsor
    total += reading;
    delay(LDRWait);
  }
//calculate the average and return it
  return total/times;
}

long getColor(){
  uint16_t colorArray[3];
  for(int c = 0;c<=2;c++){
    if (c == 0){
        led.setColor(255,0,0);    
      } else if (c == 1){
        led.setColor(0,255,0);  
      } else {
       led.setColor(0,0,255);  
      } //turn ON the LED, red, green or blue, one colour at a time.
      led.show();
      delay(RGBWait);
      colorArray[c] = getAvgReading(5);
      led.setColor(0,0,0);
      led.show();
      delay(RGBWait);
      
  }
  if (colorArray[0] > 210 && colorArray[0]< 240 && colorArray[1]> 140 && colorArray[1]< 160 && colorArray[2]> 130 && colorArray[2]< 150) {
    // return green
    //Serial.println("Green");
    return GREEN;
  
  } else if (colorArray[0] > 275 && colorArray[0]< 305 && colorArray[1]> 115 && colorArray[1]< 135 && colorArray[2]> 125 && colorArray[2]< 150) {
 //   Serial.println("Red");
    return RED;
  } else if (colorArray[0] > 300 && colorArray[0]< 350 && colorArray[1]> 155 && colorArray[1]< 185 && colorArray[2]> 135 && colorArray[2]< 165) {
  //  Serial.println("Yellow");
    return YELLOW;  
  }  else if (colorArray[0] > 250 &&/* colorArray[0]< 270 &&*/ colorArray[1]> 155 && colorArray[1]< 200 /*&& colorArray[2]> 175 && colorArray[2]< 210*/){
  //  Serial.println("Blue");
    return BLUE;  
  } else if (colorArray[0] > 240 && /*colorArray[0]< 270 &&*/ colorArray[1]> 135 && colorArray[1]< 155 /*&& colorArray[2]> 160 && colorArray[2]< 180*/) {
 //   Serial.println("Purple");
    return PURPLE;
  } 
 // Serial.println("Black");
  return BLACK;
  
}
