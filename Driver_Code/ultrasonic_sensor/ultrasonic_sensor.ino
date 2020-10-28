


#include "MeMCore.h"
#define MIN_DISTANCE 69
MeUltrasonicSensor ultraSensor(PORT_7); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */
bool front_too_close ( double distance) {
  return (distance < MIN_DISTANCE);
}
/*
 * void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  delay(100); 
 }
 
 */
 
