#include "colorSensor.h"
ColorDetector::ColorDetector(){
}

ColorDetector::calibrate(){
	for (int i = 0; i < 6; i += 1){
	//turn on one colour at a time and LDR reads 5 times
		Serial.println(colourStr[i]);
		for(int c = 0;c<=2;c++){    
			Serial.print(colourStr[c]);
			if (c == 0){
			  led.setColor(255,0,0);    
			} else if (c == 1){
			  led.setColor(0,255,0);  
			} else {
			 led.setColor(0,255,0);  
			 } //turn ON the LED, red, green or blue, one colour at a time.
			delay(RGBWait);
		//get the average of 5 consecutive readings for the current colour and return an average 
			getRangeReading(25,i,c);
		//the average reading returned minus the lowest value divided by the maximum possible range, multiplied by 255 will give a value between 0-255, representing the value for the current reflectivity (i.e. the colour LDR is exposed to)
		//	colourArray[c] = (colourArray[c] - blackArray[c])/(greyDiff[c])*255;
			led.setColor(0,0,0);  //turn off the current LED colour
			delay(RGBWait);
		}
		delay(CALWait);	  
	}	
	// now arbiitraily set ranges
}

void ColorDetector::getRangeReading(int times,int paper, int color){
	uint16_t min = 65535;
	uint16_t max = 0;
	for(int i = 0;i < times;i++){
		reading. = lightSensor.read();  // to change to lightsencsor
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
	
	Serial.println(int(colorRange[i][c][0]));
	Serial.print(" ");
	Serial.println(int(colorRange[i][c][1])); 
}

uint16_t ColorDetector::getAvgReading(int times){      
//find the average reading for the requested number of times of scanning LDR
  uint16_t reading;
  uint16_t total =0;
//take the reading as many times as requested and add them up
	uint16_t min = 65535;
	uint16_t max = 0;
  for(int i = 0;i < times;i++){
    reading. = lightSensor.read();  // to change to lightsencsor
    total += reading;
	delay(LDRWait);
  }
//calculate the average and return it
  return total/times;
}

/**
 * Returns a number representing 1 of 6 possible colors from 1 to 6
 *
*/
long ColorDetector::getColor(){
	uint16_t reading. = lightSensor.read();
	
}




