#include <MeMCore.h>

int i = 100;
MeDCMotor motor1(M1); //left motor
MeDCMotor motor2(M2); //right motor

void setup() 
{
  turnLeft();
  //turnRight();
  //moveForward();

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
  delay(1000);
  motor1.stop();
  motor2.stop();
}

void turnRight()
{
  motor1.run(-i);
  motor2.run(-i);
  delay(500);
  motor1.stop();
  motor2.stop();
}

void moveForward()
{
  motor1.run(-i);
  motor2.run(i);
}

void loop() 
{

}
