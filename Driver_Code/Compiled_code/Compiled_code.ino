#include <MeMCore.h>


// mising color() to check the color
// IR to check the distance
MeLineFollower lineFinder(PORT_1);
MeUltrasonicSensor ultraSensor(PORT_3);
MeBuzzer buzzer;
MeDCMotor motor1(M1); //left motor
MeDCMotor motor2(M2); //right motor

#define NEAR_WALL 4 ;//for two cases the value may need to be changed
int i = 150; // analog value to control speed of motor
bool finished = false;

void setup() 
{
  // put your setup code here, to run once:
  
  //running through the maze
  while (!finished) 
  {
    if (front_near_wall() && find_black_line()) 
    {
      stop();
      checkColor();
    } 
    else 
    {
      moveForward();
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

//decide 
void turning()
{
  if(color() == RED) 
  {
    //turn left
    turnLeft();
  }
  else if(color() == GREEN) 
  {
    //turn right
    turnRight();
  }
  else if(color() == YELLOW) 
  {
    // 180 degree in a same grid
    UTurn();
  }
  else if(color() == PURPLE) 
  {
    // two successive left turns
    doubleLeft();
  }
  else if(color() == LIGHT_BLUE) 
  {
    //two successive right turns
    doubleRight();
  }
  else if(color() == BLACK)
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
/*
void adjustLeft() // to be used if mbot is not moving straight based on data from the ir sensors
{
 while()
 {
   motor1.run(-i);
   motor2.run(i+10);
 }
}
void adjustRight() // to be used if mbot is not moving straight based on data from the ir sensors
{
 while()
 {
   motor1.run(-i-10);
   motor2.run(i);
 }
}*/

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
