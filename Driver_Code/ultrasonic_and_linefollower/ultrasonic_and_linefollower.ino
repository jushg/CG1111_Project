

MeLineFollower lineFinder(PORT_1)
MeUltrasonicSensor ultraSensor(PORT_3);

#define NEAR_WALL 4
bool front_near_wall() 
{
  double distance = ultraSensor.distanceCm();
  return (distance < NEAR_WALL);
}

bool find_black_line() {
  int sensorState = lineFinder.readSensors();
  return (sensorState == S1_IN_S2_IN); 
}
