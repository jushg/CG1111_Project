#include "MeMCore.h"
#include "Wire.h"
#define RGBWait 200 //in milliseconds 

// Define time delay before taking another LDR reading
#define LDRWait 10 //in milliseconds 

#define CALWait 5000
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define PURPLE 5
#define BLACK 6

char colourStr[6][5] = {"R = ", "G = ", "B = ", "Y= ", "P= ","B="};
    
//long colorRange[5][3]] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
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
MeRGBLed led(0, 30);
MeLightSensor lightSensor(PORT_8);
void setup() {
  // put your setup code here, to run once:
  led.setpin(13);
  //led.setColor(0,255,0);
  //led.show();
  Serial.begin(9600);
  calibrate();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void calibrate(){
  for (int i = 0; i < 1; i += 1){
  //turn on one colour at a time and LDR reads 5 times
    Serial.println(colourStr[i]);
    for(int c = 0;c<=2;c++){    
      Serial.print(colourStr[c]);
      if (c == 0){
        led.setColor(255,0,0);    
        
      } else if (c == 1){
        led.setColor(0,255,0);  
      } else {
       led.setColor(0,0,255);  
      } //turn ON the LED, red, green or blue, one colour at a time.
       
  led.show();
      delay(RGBWait);
    //get the average of 5 consecutive readings for the current colour and return an average 
      getRangeReading(25,i,c);
    //the average reading returned minus the lowest value divided by the maximum possible range, multiplied by 255 will give a value between 0-255, representing the value for the current reflectivity (i.e. the colour LDR is exposed to)
    //  colourArray[c] = (colourArray[c] - blackArray[c])/(greyDiff[c])*255;
      led.setColor(0,0,0);  //turn off the current LED colour
      
  led.show();
      delay(RGBWait);
    }
    delay(CALWait);   
  } 
  // now arbiitraily set ranges
}

void getRangeReading(int times,int paper, int color){
  uint16_t min = 65535;
  uint16_t max = 0;
  for(int i = 0;i < times;i++){
    uint16_t reading = lightSensor.read();  // to change to lightsencsor
    if (min > reading) {
      min = reading;
    }
    if (max < reading) {
      max = reading;
    }
    Serial.println(max);
    Serial.println(min);
    delay(LDRWait);
  }
  colorRange[paper][color][0] = min;
  colorRange[paper][color][1] = max;
  
  Serial.println(int(colorRange[paper][color][0]));
  Serial.print(" ");
  Serial.println(int(colorRange[paper][color][1])); 
}

long ColorDetector::getColor(){
  uint16_t reading = lightSensor.read();
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
      uint16_t reading[c] = getAvgReading(5);
  }
  //Get three diffs
   r_min_g = colorArray[0] - colorArray[1];
   r_min_b = colorArray[0] - colorArray[2];
   g_min_b = colorArray[1] - colorArray[2];
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

uint16_t getAvgReading2(int times){      
//find the average reading for the requested number of times of scanning LDR
  uint16_t reading;
  uint16_t total =0;
//take the reading as many times as requested and add them up
  uint16_t min = 65535;
  uint16_t max = 0;
  for(int i = 0;i < times;i++){
    reading = lightSensor.read();  // to change to lightsencsor
    if (min > reading) {
      min = reading;
    }
    if (max < reading) {
      max = reading;
    }
    delay(LDRWait);
  }
  //calculate the average and return it
  return (max+min)/2;
}
