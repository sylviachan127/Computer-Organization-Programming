//Yuen Han Chan
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pikachu.h"
#include "mylib.h"
#include "evil.h"
#include "candy.h"
#include "title.h"
#include "lose.h"

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLED;
	int gameStart = 0;
	int gameEnd = 0;
	int maxCandy = 4;
	int MAXenemy = 25;
	int maxHorEnemy = 5;
	int delay = 1;
	int levelIncrease = 15;


	Range enemyRange[MAXenemy];

	Candy candys[maxCandy];

	Enemy horEnemy[MAXenemy];
	Enemy oldHorEnemy[MAXenemy];


	u16 tryColor = RGB(rand()%32, rand()%32, rand()%32);
	u16 tryColor2 = RGB(rand()%32, rand()%32, rand()%32);
	u16 tryColor3 = RGB(rand()%32, rand()%32, rand()%32);
	drawRect(40,0,25,240,WHITE);
	drawRect(65,0,25,240,YELLOW);
	drawRect(90,0,25,240,tryColor);
	drawRect(115,0,25,240,tryColor2);
	drawRect(115+25,0,25,240,tryColor3);
	
	int enemySize = 15;
	int candySize = 15;
	int pikaSize = 15;
	int life = 3;
	int score = 0;
	bool restartPos = false;
	int level = 1;
	Player pika = {40-pikaSize-2, 80};
	Player oldPika = {40-pikaSize-2, 80};

	for(int i = 0; i<maxHorEnemy; i++){
		enemyRange[i].x1 = (rand()%200);
		enemyRange[i].x2 = enemyRange[i].x1 + 40;
	}

	for(int i = 0; i<maxHorEnemy; i++){
		horEnemy[i].r = (rand()%120)+40;
		horEnemy[i].c = enemyRange[i].x1;
		oldHorEnemy[i] = horEnemy[i];
	}

	for(int i = 0; i<maxCandy; i++){
		candys[i].r = ((rand()%(160-candySize-40))+40);
		candys[i].c = rand()%(240-candySize);
		drawImage3(candys[i].r, candys[i].c, candySize, candySize, candy);
	}


  	while(1) {
  		while(!gameStart){
		waitForVblank();
			drawImage3(0, 0, 240, 160, title);
			drawString(0,0,"Testing", RED);
			if(KEY_DOWN_NOW(BUTTON_A)){
				gameStart=1;
				drawRect(0,0,40,240,BLACK);
				drawRect(40,0,25,240,WHITE);
				drawRect(65,0,25,240,YELLOW);
				drawRect(90,0,25,240,tryColor);
				drawRect(115,0,25,240,tryColor2);
				drawRect(115+25,0,25,240,tryColor3);
			};
		}

  		while(gameStart){
			waitForVblank();
			/* Display Score */
			drawString(2,160,"Score:",WHITE);
			sprintf(buffer, "%d", score);
			drawRect(2, 200, 10, 30, BLACK);
			drawString(2,200,buffer,WHITE);

			/* Display Level */
			drawString(2,3,"Level:",WHITE);
			sprintf(buffer, "%d", level);
			drawRect(2, 40, 10, 30, BLACK);
			drawString(2,40,buffer,WHITE);

			/* Display Life */
			drawString(15,160,"Life:",WHITE);
			sprintf(buffer, "%d", life);
			drawRect(15, 200, 10, 30, BLACK);
			drawString(15,200,buffer,WHITE);

			oldPika = pika;
			if(KEY_DOWN_NOW(BUTTON_LEFT)){
				if((pika.c)>0){
					pika.c-=1;
				}
			}
			if(KEY_DOWN_NOW(BUTTON_RIGHT)){
				if((pika.c+pikaSize)<240){
					pika.c+=1;
				}
			}
			if(KEY_DOWN_NOW(BUTTON_UP)){
				if(pika.r>23){
					pika.r-=1;
				}
			}
			if(KEY_DOWN_NOW(BUTTON_DOWN)){
				if((pika.r+pikaSize)<160){
					pika.r+=1;
				}
			}
			drawRect(oldPika.r, oldPika.c, pikaSize, pikaSize, BLACK);
			drawImage3(pika.r, pika.c, pikaSize,pikaSize, pikachu);
			//oldPika = pika;
			for(int i = 0; i<maxHorEnemy; i++){
				oldHorEnemy[i] = horEnemy[i];
			}

			//draw Enemy movements
			for(int i = 0; i<maxHorEnemy; i++){
				drawRect(oldHorEnemy[i].r, oldHorEnemy[i].c, enemySize, enemySize, BLACK);
				if(horEnemy[i].c < enemyRange[i].x2){
					horEnemy[i].c += 1;
				}
				 if(horEnemy[i].c==enemyRange[i].x2){
					enemyRange[i].x2 = enemyRange[i].x1;
				}
				 if(enemyRange[i].x2<horEnemy[i].c){
					horEnemy[i].c -=1;
				}
				 if(horEnemy[i].c == enemyRange[i].x1){
					enemyRange[i].x2 = enemyRange[i].x1 +40;
				}
				if((horEnemy[i].c == pika.c)&&(horEnemy[i].r == pika.r)){
					life--;
				}
				drawImage3(horEnemy[i].r, horEnemy[i].c, enemySize, enemySize, evil);
			}

			for(int i = 0; i<maxCandy; i++){
				//check for collision between player and candys
				if(collide(pika.r,pika.c,pikaSize,candys[i].r,candys[i].c,candySize)){
					score += 1;
					drawRect(candys[i].r, candys[i].c, candySize, candySize, BLACK);
					candys[i].r = ((rand()%(160-candySize-40))+40);
					candys[i].c = rand()%(240-candySize);
				}
				drawImage3(candys[i].r, candys[i].c, candySize, candySize, candy);
			}

			for(int i = 0; i<maxHorEnemy; i++){
				if(collide(pika.r,pika.c,pikaSize,horEnemy[i].r,horEnemy[i].c,enemySize)){
					if(!delay){
						life-=1;
						delay++;
					}
				}
			}

			for(int i = 0; i<maxCandy; i++){
				for(int j = 0; j<maxHorEnemy; j++){
					if(collide(candys[i].r,candys[i].c,candySize,horEnemy[j].r,horEnemy[j].c,enemySize)){
						drawRect(candys[i].r, candys[i].c, candySize, candySize, BLACK);
						candys[i].r = ((rand()%(160-candySize-40))+40);
						candys[i].c = rand()%(240-candySize);
					}
				}
			}

			if((score>=levelIncrease)&&(score%levelIncrease==0)&&(restartPos!=true)){
				restartPos = true;
			}
			if(restartPos){
				u16 tryColor = RGB(rand()%32, rand()%32, rand()%32);
				u16 tryColor2 = RGB(rand()%32, rand()%32, rand()%32);
				u16 tryColor3 = RGB(rand()%32, rand()%32, rand()%32);
				drawRect(pika.r, pika.c, pikaSize, pikaSize, BLACK);
				pika.r = 40-pikaSize-2;
				pika.c = 80;
				oldPika = pika;
				drawRect(40,0,25,240,WHITE);
				drawRect(65,0,25,240,YELLOW);
				drawRect(90,0,25,240,tryColor);
				drawRect(115,0,25,240,tryColor2);
				drawRect(115+25,0,25,240,tryColor3);
				level++;
				score+=1;
				delay=1;
				if(maxHorEnemy<MAXenemy){
					maxHorEnemy+=1;
					if(level%3==0){
						life++;
					}
				}
				for(int i = 0; i<maxHorEnemy; i++){
					enemyRange[i].x1 = (rand()%200);
					enemyRange[i].x2 = enemyRange[i].x1 + 40;
				}

				for(int i = 0; i<maxHorEnemy; i++){
					horEnemy[i].r = (rand()%120)+40;
					horEnemy[i].c = enemyRange[i].x1;
					oldHorEnemy[i] = horEnemy[i];
				}
				restartPos = false;
			}

			if(life==0){
				gameEnd=1;
				gameStart=0;
			}

			if(delay){
				delay++;
			}

			if(delay==50){
				delay=0;
			}
		}

		while(gameEnd){
			drawImage3(0, 0, 240, 160, lose);
			if(KEY_DOWN_NOW(BUTTON_A)){
				life = 3;
				score = 0;
				drawRect(0,0,40,240,BLACK);
				gameStart=1;
				drawRect(40,0,25,240,WHITE);
				drawRect(65,0,25,240,YELLOW);
				drawRect(90,0,25,240,tryColor);
				drawRect(115,0,25,240,tryColor2);
				drawRect(115+25,0,25,240,tryColor3);
				pika.r = 40-pikaSize-2;
				pika.c = 80;
				maxHorEnemy = 5;
				delay = 1;
				level = 1;
				gameEnd = 0;
			}
		}
	}
	return 0;
}




