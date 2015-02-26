#include "Enemy.h"
#include <math.h>

Enemy::Enemy(int x, int y){
	rect.x = x;
	rect.y = y;
	rect.w = 100;
	rect.h = 100;
	lastTime = SDL_GetTicks();
}

void Enemy::move(int target[]){
	currentTime = SDL_GetTicks();
	float timePassed = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	float distance = sqrt(pow((float)target[0] - rect.x, 2) + pow((float)target[1] - rect.y, 2));
	float sin = (target[1] - rect.y) / distance;
	float cos = (target[0] - rect.x) / distance;
	
	rect.x = (int)(cos*moveSpeed*timePassed);
	rect.y = (int)(sin*moveSpeed*timePassed);
}

void Enemy::refreshCoordBuffer(int x, int y){
	coordBuffer[0] = x;
	coordBuffer[1] = y;
}

int* Enemy::getCoords(){
	return coordBuffer;
}

SDL_Rect* Enemy::getRect(){
	return &rect;
}