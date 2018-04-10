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

void drawRect(int r, int c, int width, int height, u16 color)
{
	for(int x=0; x<width; x++){
		for(int y=0; y<height; y++){
			setPixel(y+r,x+c,color);
		}
	}
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

bool collide(int r, int c, u16 color){
	return *(videoBuffer + OFFSET(r,c,240)) == color;
}

void drawBullet(int r, int c){
	drawRect(r, c, 2, 3, RED);
	drawRect(r+2, c, 2, 3, BLACK);
}

void drawEnemyBullet(int r, int c, u16 color){
	drawRect(r, c, 2, 3, color);
	drawRect(r-2, c, 2, 3, BLACK);
}

void layoutEnemy(int maxX, int maxY, u16 color)
{
	int t=0;
	for(int a = 25; a<maxX; a+=30) {
		for(int b = 5; b<maxY; b+=30) {
			drawRect(b, a+t, 16, 16, color);
			//t+=4;
		}
	}
}

void gameEnd(){
	drawRect(0,0,240, 160, RED);
}

void delay(int n)
{
	volatile int i;
	for(i=0; i<n*10000; i++)
	{
	
	}
}

void endGame(int score){
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
	drawString(60,85,"YOU LOSE",RED);
	drawString(75,70,"YOUR SCORE IS:",COLOR2);
	sprintf(buffer, "%d", score);
	drawString(75,155,buffer,COLOR2);

}

void waitForVblank()
{
	while(SCANLINECOUNTER >= 160);
	while(SCANLINECOUNTER < 160);
}



