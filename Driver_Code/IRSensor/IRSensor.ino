#define THRESHOLD0 2.4
#define THRESHOLD1 3.6
#define RIGHT A1
#define LEFT A0
#include "MeOrion.h"
//#include <MeMCore.h>
#include <SoftwareSerial.h>

int i = 150;
//int a = 0;
//int b = 0;
MeDCMotor motor1(M1); //left motor
MeDCMotor motor2(M2); //right motor

MeInfraredReceiver infraredReceiverDecode(PORT_4);

void setup()
{
  infraredReceiverDecode.begin();
  Serial.begin(9600);
}

void adjustLeft() { // too close to right
  //double v = analogRead(RIGHT) / 1023.0 * 5;
  //if (v < THRESHOLD1) {
    Serial.println("LEFT");
    motor1.run(-i);
    motor2.run(i+10);
    delay(100);
  //}
   /*motor1.run(-i-10);
   motor2.run(i);
   delay(500);
   motor1.run(i);
   motor2.run(i);*/
}

void adjustRight() { // too close to left
  //double v = analogRead(LEFT) / 1023.0 * 5;
  //if (v < THRESHOLD0) {
    Serial.println("RIGHT");
    motor1.run(-i-10);
    motor2.run(i);
    delay(100);
  //}
    /*motor1.run(-i);
    motor2.run(i+10);
    delay(50);
    motor1.run(i);
    motor2.run(i);*/
}

void moveForward()
{
  motor1.run(-i);
  motor2.run(i);
}

void loop() {
  moveForward();
  double left = analogRead(LEFT) / 1023.0 * 5;
  double right = analogRead(RIGHT) / 1023.0 *5;
  if (left < THRESHOLD0) {
  adjustLeft();
  }
  if (right < THRESHOLD1) {
  adjustRight();
  }
  if (left > THRESHOLD0 && right > THRESHOLD1) {
    moveForward90;
  }

  /*double v0 = analogRead(LEFT)/ 1023.0 * 5;
  double v1 = analogRead(RIGHT)/ 1023.0 * 5;
  //Serial.print(" , ");
  Serial.print(v0);
  Serial.print(" , ");
  Serial.println(v1);
  while (v0 < THRESHOLD0) {
    Serial.println("SKEW RIGHT");
    motor1.run(-i);
    motor2.run(i+10);
  }
  while (v1 < THRESHOLD1) {
    Serial.println("SKEW LEFT");
    motor1.run(-i-10);
    motor2.run(i);
  }
  delay(100);*/
}
