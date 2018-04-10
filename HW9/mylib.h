//Yuen Han Chan
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef _MYLIB_

typedef unsigned short u16;
extern u16 *videoBuffer;

char buffer[100];

#define _MYLIB_
#define OFFSET(r,c,rowlen) ((r)*(rowlen)+(c))
#define REG_DISPCTL *(unsigned short *)0x4000000  //access location 0x4000000 and get u16 
									  //that's located inside
#define MODE3 3
#define BG2_ENABLED (1<<10)
//#define SETMODE(mde) REG_DISPCNT = (mode)
#define RGB(r,g,b) ((r)|((g)<<5)|((b)<<10))
#define RED RGB(31,0,0)
#define BLUE RGB(0,0,31)
#define WHITE RGB(31, 31, 31)
#define BLACK RGB(0,0,0)
#define YELLOW RGB(31,31,0)
#define COLOR1 RGB(23,5,14)
#define COLOR2 RGB(18,5,25)
#define COLOR3 RGB(11,10,22)


/* Buttons */
#define BUTTON_A      (1<<0)
#define BUTTON_B      (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START  (1<<3)
#define BUTTON_RIGHT  (1<<4)
#define BUTTON_LEFT   (1<<5)
#define BUTTON_UP     (1<<6)
#define BUTTON_DOWN   (1<<7)
#define BUTTON_R      (1<<8)
#define BUTTON_L      (1<<9)

#define BUTTONS (*( volatile unsigned int *)0x04000130)
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)

void setPixel(int r, int c, u16 color);
void setBlack(int r, int c, int width, int height);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void plotLine(int x0, int y0, int x1, int y1, u16 color);
void waitForVblank();
//void shoot(int r, int c, int width, int height, u16 color);
void delay(int n);
bool collide(int r, int c, u16 color);
void layoutEnemy(int maxX, int maxY, u16 color);
void drawBullet(int r, int c);
void drawEnemyBullet(int r, int c, u16 color);
void gameEnd();
//bool collideEnemy(int r, int c, u16 color);
void drawChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char *str, unsigned short color);
void endGame(int score);

typedef struct
{
	int r;
	int c; 
	//bool used;
} Point, Bullet;

#endif
