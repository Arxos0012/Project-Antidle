#include "Enemy.h"
#include <math.h>
#include <iostream>

Enemy::Enemy(int x, int y){
	worldRect.x = x;
	worldRect.y = y;
	worldRect.w = 25;
	worldRect.h = 25;

	screenRect.w = 25;
	screenRect.h = 25;
}

void Enemy::move(float* target, float time){
	float distance = sqrt(pow(target[0] - worldRect.x, 2) + pow(target[1] - worldRect.y, 2));
	if (distance <= 25) return;

	float cos = (target[0] - worldRect.x) / distance;
	float sin = (target[1] - worldRect.y) / distance;
	
	float xSpeed = cos*moveSpeed*time;
	float ySpeed = sin*moveSpeed*time;

	collectiveX += xSpeed;
	collectiveY += ySpeed;

	if (collectiveX >= 1 || collectiveX <= -1){
		worldRect.x += collectiveX;
		collectiveX = 0;
	}
	if (collectiveY >= 1 || collectiveY <= -1){
		worldRect.y += collectiveY;
		collectiveY = 0;
	}
}


void Enemy::getCoords(int* coords){
	coords[0] = worldRect.x;
	coords[1] = worldRect.y;
}

SDL_Rect* Enemy::getScreenRect(){
	return &screenRect;
}

void Enemy::refeshScreenCoords(int* coords){
	screenRect.x = coords[0];
	screenRect.y = coords[1];
}