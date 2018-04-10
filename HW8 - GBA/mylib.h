//Yuen Han Chan
#ifndef _MYLIB_

typedef unsigned short u16;
extern u16 *videoBuffer;

#define _MYLIB_
#define OFFSET(r,c) ((r)*240+(c)) 
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

void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void plotLine(int x0, int y0, int x1, int y1, u16 color);

#endif
