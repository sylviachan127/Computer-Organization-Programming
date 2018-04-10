//Yuen Han Chan
#include <stdio.h>
#include "mylib.h"

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLED;
	//drawRect(73,14,13,35,RED);
	drawRect(0,0,240,160,WHITE);
	int x=0, y=0, maxX=240, maxY=160;
	for(int count=0; count<3; count++){		//broader 1
		drawHollowRect(y, x, maxX, maxY, COLOR1);
		y=y+1;
		x=x+1;
		maxY=maxY-2;
		maxX=maxX-2;
	}
	x=3, y=3, maxX=234, maxY=154;
	for(int count=0; count<3; count++){		//broader 2		
		drawHollowRect(y, x, maxX, maxY, COLOR2);
		y=y+1;
		x=x+1;
		maxY=maxY-2;
		maxX=maxX-2;
	}
	drawRect(10, 100, 50, 7, BLACK); //Top Line
	drawRect(17, 85, 15, 7, BLACK);
	drawRect(24, 77, 8, 7, BLACK);
	drawRect(31, 69, 8, 20, BLACK);
	drawRect(51, 61, 8, 40, BLACK);
	drawRect(91, 69, 23, 7, BLACK); 
	drawRect(84, 92, 64, 7, BLACK);  //Bottom black line
	drawRect(91, 156, 23, 7, BLACK);
	drawRect(51, 179, 8, 40, BLACK);
	drawRect(31, 171, 8, 20, BLACK);
	drawRect(24, 163, 8, 7, BLACK);
	drawRect(17, 150, 15, 7, BLACK);  //Upper Head Complete
	drawRect(98, 77, 8, 20, BLACK);
	drawRect(118, 85, 8, 7, BLACK);
	drawRect(125, 92, 64, 7, BLACK);  //Most bottom black line
	drawRect(118, 156, 8, 7, BLACK);
	drawRect(98, 163, 8, 20, BLACK);
	drawRect(91, 105, 8, 20, COLOR3);  //First eye
	drawRect(91, 132, 8, 20, COLOR3);
	setPixel(75, 123, RED);	
	plotLine(0,0,10,10, YELLOW);
  	while(1) {
 	}
	return 0;
}

