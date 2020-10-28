#include <MeMCore.h>

int i = 150;
//int a = 0;
//int b = 0;
MeDCMotor motor1(M1); //left motor
MeDCMotor motor2(M2); //right motor

void setup() 
{
  turnLeft();
  delay(2000);
  turnRight();
  delay(2000);
  //moveForward();
  UTurn();
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

void loop()
{
  
}

/*
void doubleLeft()
{
  turnLeft();
  while(data based on ultrasonic sensor)
  {
    moveForward();
  }
  turnLeft();
}

void doubleRight()
{
  turnLeft();
  while(data based on ultrasonic sensor)
  {
    moveForward();
  }
  turnLeft();
}

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
