#include "MeMCore.h"
#include "Wire.h"
#include <limits.h>

#define RGBWait 200 //in milliseconds 

// Define time delay before taking another LDR reading
#define LDRWait 10 //in milliseconds 

#define CALWait 5000;
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define PURPLE 5
#define BLACK 6


class ColorDetector{
	public:      
		//float colourArray[] = {0,0,0};
		/*
		float whiteArray[] = {0,0,0};
		float blackArray[] = {0,0,0};
		float greyDiff[] = {0,0,0};*/
		char colourStr[6][5] = {"R = ", "G = ", "B = ", "Y= ", "P= ","B="};
		
		//long colorRange[5][3]] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
		uint16_t colorRange[6][3][2]] = {
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
		MeRGBLed led(PORT_3);
		MeLightSensor lightSensor(PORT_6);
		ColorDetector();
		void calibrate();
		void setBalance();
		int getAvgReading(int times);
		void getRangeReading(int times,int paper, int color)
		long getColor();
};	