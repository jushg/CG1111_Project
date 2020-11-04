#include <MeMCore.h>
#include "Wire.h"
#define THRESHOLD0 2.7
#define THRESHOLD1 3.6
#define WALL 1
#define RIGHT A1
#define LEFT A0

#include <SoftwareSerial.h>
 

// mising color() to check the color
// IR to check the distance
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
#define NEAR_WALL 4 //for two cases the value may need to be changed
int i = 150; // analog value to control speed of motor
bool finished = false;
char colourStr[6][5] = {"R = ", "G = ", "B = ", "Y= ", "P= ","B="};
uint16_t colorRange[6][3][2] = {
  {
    {0,65536},{0,65536},{0,65536}
  },
  {
    {0,65536},{0,65536},{0,65536}
  },
  {
    {0,65536},{0,65536},{0,65536}
  },
  {
    {0,65536},{0,65536},{0,65536}
  },
  {
    {0,65536},{0,65536},{0,65536}
  },
  {
    {0,65536},{0,65536},{0,65536}
  }
};



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
      moveForward();
      left = analogRead(LEFT) / 1023.0 * 5;
      right = analogRead(RIGHT) / 1023.0 *5;
      if (left < THRESHOLD0) {
        adjustLeft();
      }
      if (right < THRESHOLD1) {
        adjustRight();
      }
      if (left > THRESHOLD0 && right > THRESHOLD1) {
        moveForward();
      }
      if (left < WALL) {
        moveBackward();
        delay(1000);
        motor1.run(i);
        motor2.run(i);
        delay(100);
        moveForward();
      }
      if (right < WALL) {
        moveBackward();
        delay(1000);
        motor1.run(-i);
        motor2.run(-i);
        delay(100);
        moveForward();
      }
    }
  }
}

void loop() {
  
}
//decide 
void checkColor()
{
  if(getColor() == RED) 
  {
    //turn left
    turnLeft();
  }
  else if(getColor() == GREEN) 
  {
    //turn right
    turnRight();
  }
  else if(getColor() == YELLOW) 
  {
    // 180 degree in a same grid
    UTurn();
  }
  else if(getColor() == PURPLE) 
  {
    // two successive left turns
    doubleLeft();
  }
  else if(getColor() == BLUE) 
  {
    //two successive right turns
    doubleRight();
  }
  else if(getColor() == BLACK)
  {
     //finished, play song
    buzzer.tone(600, 1000);   //Buzzer sounds 600Hz for 1000ms
    delay(2000);              //Pause for 2000ms, Buzzer no sound
    buzzer.tone(1200, 1000);  //Buzzer sounds 1200Hz for 1000ms
    delay(2000);
    //finished
    finished = true;
    
  }
}
void moveForward()
{
  motor1.run(-i);
  motor2.run(i);
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
  delay(470);
  stop();
}

void turnRight()
{
  motor1.run(-i);
  motor2.run(-i);
  delay(470);
  stop();
}

void UTurn()
{
  turnLeft();
  turnLeft();
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
  turnLeft();
  while(!front_near_wall())
  {
    moveForward();
  }
  stop();
  turnLeft();
}

void adjustLeft() // to be used if mbot is not moving straight based on data from the ir sensors
{
 //double v = analogRead(RIGHT) / 1023.0 * 5;
  //if (v < THRESHOLD1) {
    motor1.run(-i);
    motor2.run(i+10);
    delay(100);
}
void adjustRight() // to be used if mbot is not moving straight based on data from the ir sensors
{
 //double v = analogRead(LEFT) / 1023.0 * 5;
  //if (v < THRESHOLD0) {
    motor1.run(-i-10);
    motor2.run(i);
    delay(100);
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
  }
  //Get three diffs
   uint16_t r_min_g = colorArray[0] - colorArray[1];
   uint16_t r_min_b = colorArray[0] - colorArray[2];
   uint16_t g_min_b = colorArray[1] - colorArray[2];
  // now test for color
  
  if (r_min_g > 10 && r_min_b < 40) {
    // return green
    return GREEN;
  } else if (r_min_g > 115 && r_min_b < 145) {
    return PURPLE;
  } else if (r_min_b > 255 && r_min_b < 285) {
    return RED;
  } else if (r_min_b > 320 && r_min_b < 350) {
    return YELLOW;  
  } else if (g_min_b > 0 && g_min_b < 35 && colorArray[0] > 300){
    return BLUE;  
  } else {
    return BLACK;  
  }
}
