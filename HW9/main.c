//Yuen Han Chan
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mylib.h"

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLED;
	int old_y = 140;
	int old_x = 0;
	int old_width = 10;
	int old_height = 10;
	int new_y = 140;
	int new_x = 0;
	int new_width = 10;
	int new_height = 10;
	const int maxX = 200;
	const int maxY = 90;
	const int maxBulletCount = 10;
	const int maxEnemyBullet = 5;
	int randomX=100;
	int oldRandomX = 100;
	bool end = false;
	int score = 0;
	int life = 6;
	//char buffer[100];
	int timeLeft = 50000;


	Bullet bullets[maxBulletCount];
	Bullet enemys[maxEnemyBullet];

	u16 tryColor = RGB(rand()%32, rand()%32, rand()%32);
	layoutEnemy(maxX, maxY, BLUE);

	for(int a = 0; a<maxBulletCount; a++){
		bullets[a].r = bullets[a].c = -10;
	}

	for(int a = 0; a<maxEnemyBullet; a++){
		enemys[a].r = enemys[a].c = maxY;
	}

  	while(1) {
  		if(!end){
  			drawRect(45,200,30,15,BLACK);
  			drawRect(75,200,30,15,BLACK);
  			timeLeft--;
  			if(timeLeft==0){
  				end=true;
  			}
  			drawString(2,200,"Score:",WHITE);
  			sprintf(buffer, "%d", score);
  			drawString(15,200,buffer,WHITE);

  			drawString(30,200,"Time:",WHITE);
  			sprintf(buffer, "%d", timeLeft);
  			drawString(45,200,buffer,WHITE);
  			//drawRect(45,200,30,20,BLACK);

  			drawString(60,200,"Life:", WHITE);
  			sprintf(buffer, "%d", life);
  			drawString(75,200,buffer,WHITE);

	  		drawHollowRect(maxY, oldRandomX, 15, 15, BLACK);
	  		drawHollowRect(maxY, randomX, 15, 15, WHITE);
	  		oldRandomX = randomX;

	  		if((rand()%3)==1){
	  			randomX-=1;
	  		}
	  		else{
	  			randomX+=1;
	  		}

			if(KEY_DOWN_NOW(BUTTON_UP))
			{	

				
				int i;
				for(i = 0; i<maxBulletCount; i++){
					if(bullets[i].r == -10){
						break;
					}
				}

				if(i < maxBulletCount){
					bullets[i].r = new_y-1;
					bullets[i].c = new_x;
				}
			}

			int chance = rand()%10;
			if(chance==2){
				int i;
				for(i = 0; i<maxEnemyBullet; i++){
					if(enemys[i].r == 180){
						break;
					}
				}

				if(i < maxEnemyBullet){
					enemys[i].r = maxY+20;
					enemys[i].c = randomX;
				}
			}

			for(int a=0; a<maxEnemyBullet; a++){

				if(enemys[a].r<180){
					enemys[a].r+=1;
					drawEnemyBullet(enemys[a].r, enemys[a].c, tryColor);
				}

				if(collide(enemys[a].r+3, enemys[a].c, COLOR3)){
					life--;
					if(life==0){
						end = true;
					}
				}
			}

			for(int a=0; a<maxBulletCount; a++){
				bool dead = false;

				if(bullets[a].r>-10){
					bullets[a].r-=1;
					drawBullet(bullets[a].r, bullets[a].c);
				}

				if(collide(bullets[a].r-1, bullets[a].c, BLUE)){
					score++;
					drawRect(15,200,30,15,BLACK);
					setBlack(bullets[a].r, bullets[a].c, 3, 5);
					setBlack(bullets[a].r-3, bullets[a].c-2, 3, 5);
					bullets[a].r = bullets[a].c = -10;
					dead = true;
				}
				if(dead){
					bullets[a].r = bullets[a].c = -10;
				}
			}

			if(KEY_DOWN_NOW(BUTTON_LEFT))
			{
				if((new_x-1)>10){
				new_x-=1;
				}
			}

			if(KEY_DOWN_NOW(BUTTON_RIGHT))
			{
				if((new_x+1)<250){
				new_x+=1;
				}
			}
			waitForVblank();
			drawRect(old_y, old_x, old_width, old_height, BLACK);
			drawRect(new_y, new_x, new_width, new_height, COLOR3);
			old_x=new_x;
			old_y=new_y;
			tryColor = RGB(rand()%32, rand()%32, rand()%32);
		}
		if(end){
			endGame(score);
			break;
		}
	}
	return 0;
}




