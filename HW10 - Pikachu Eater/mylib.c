//Yuen Han Chan
#include <stdio.h>
#include <stdbool.h>
#include "mylib.h"
#include "font.h"

u16 *videoBuffer = (u16 *)0x6000000;

void setPixel(int r, int c, u16 color)
{
	*(videoBuffer + OFFSET(r,c,240)) = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	int r;
	for(r=0; r<height; r++)
	{
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}

void drawLayout(){
	//sdrawRect(100, 0, 260, 20, YELLOW);
	drawRect(10,10,10,10,WHITE);
}

void setBlack(int r, int c, int width, int height)
{
	drawRect(r, c, width, height, BLACK);
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

void drawChar(int row, int col, char ch, unsigned short color) {
  int r, c;
  for (r = 0; r < 8; r++) {
    for (c = 0; c < 6; c++) {
      if (fontdata_6x8[OFFSET(r,c,6)+ch*48]) {
	setPixel(row+r, col+c, color);
      }
    }
  }
}

void drawString(int row, int col, char *str, unsigned short color) {
  while(*str) {
    drawChar(row, col, *str++, color);
    col += 6;
  }
}


void delay(int n)
{
	volatile int i;
	for(i=0; i<n*10000; i++)
	{
	
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER >= 160);
	while(SCANLINECOUNTER < 160);
}

void drawImage3(int r, int c, int width, int height, const u16* image) {
	for (int i = 0; i < height; i++) {
	    DMA[3].src = (image+i*width);
		DMA[3].dst = (videoBuffer+OFFSET(r,c,240)+i*240);
		DMA[3].cnt = width|DMA_NOW|DMA_ON;
	}
}

bool collide(int playerR,int playerC,int playerSize,int objectR,int objectC,int objectSize){
	bool result = false;
	if(
				(
					((playerR)<=(objectR)) &&
					((objectR)<=(playerR+objectSize)) &&
					((playerC)<=(objectC)) &&
					((objectC)<=(playerC+objectSize))
				) ||
				(
					((playerR)<=(objectR+objectSize)) &&
					((objectR+objectSize)<=(playerR+objectSize)) &&
					((playerC)<=(objectC)) &&
					((objectC)<=(playerC+objectSize))
				) ||
				(
					((playerR)<=(objectR)) &&
					((objectR)<=(playerR+objectSize)) &&
					((playerC)<=(objectC+objectSize)) &&
					((objectC+objectSize)<=(playerC+objectSize))
				) || (
					((playerR)<=(objectR+objectSize)) &&
					((objectR+objectSize)<=(playerR+objectSize)) &&
					((playerC)<=(objectC+objectSize)) &&
					((objectC+objectSize)<=(playerC+objectSize))
				)

					){
		result = true;
	}
	return result;
}

bool collideSame(int playerR,int playerC,int playerSize,int objectR,int objectC,int objectSize){
	bool result = false;
	if(
				(
					((playerR)==(objectR)) &&
					((objectR)==(playerR+objectSize)) &&
					((playerC)==(objectC)) &&
					((objectC)==(playerC+objectSize))
				) ||
				(
					((playerR)==(objectR+objectSize)) &&
					((objectR+objectSize)==(playerR+objectSize)) &&
					((playerC)==(objectC)) &&
					((objectC)==(playerC+objectSize))
				) ||
				(
					((playerR)==(objectR)) &&
					((objectR)==(playerR+objectSize)) &&
					((playerC)==(objectC+objectSize)) &&
					((objectC+objectSize)==(playerC+objectSize))
				) || (
					((playerR)==(objectR+objectSize)) &&
					((objectR+objectSize)==(playerR+objectSize)) &&
					((playerC)==(objectC+objectSize)) &&
					((objectC+objectSize)==(playerC+objectSize))
				)

					){
		result = true;
	}
	return result;
}


