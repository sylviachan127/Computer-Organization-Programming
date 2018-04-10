//Yuen Han Chan
#include <stdio.h>
#include "mylib.h"
u16 *videoBuffer = (u16 *)0x6000000;

void setPixel(int r, int c, u16 color)
{
	*(videoBuffer + OFFSET(r,c)) = color;
}

void drawRect(int r, int c, int width, int height, u16 color)
{
	for(int x=0; x<width; x++){
		for(int y=0; y<height; y++){
			setPixel(y+r,x+c,color);
		}
	}
}

void drawHollowRect(int r, int c, int width, int height, u16 color)
{
	for(int x=0; x<height; x++)
	{
		setPixel(x+r,c,color);
		setPixel(x+r,width+c-1,color);
	}
	for(int y=0; y<width; y++){
		setPixel(r,y+c,color);
		setPixel(r-1+height,y+c,color);
	}
}

void plotLine(int x0, int y0, int x1, int y1, u16 color)
{
	int dx = x1-x0;
	int dy = y1-y0;
	
	int D = ((dy+dy)-dx);
	setPixel(x0,y0,color);
	int y=y0;
	for(int x=(x0+1); x<=x1; x++){
		if(D>0){
			y = y+1;
			setPixel(x,y,color);
			D = (D + ((dy+dy)+(dx-dx)));
		}
		else{
			setPixel(x,y,color);
			D = (D + (dy+dy));
		}
	}
}



