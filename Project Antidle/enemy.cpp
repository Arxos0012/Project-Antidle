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
	timeCollected += time;
	float distance = sqrt(pow(target[0] - worldRect.x, 2) + pow(target[1] - worldRect.y, 2));
	if (distance == 0) return;

	float cos = (target[0] - worldRect.x) / distance;
	float sin = (target[1] - worldRect.y) / distance;
	
	float xSpeed = cos*moveSpeed*time;
	float ySpeed = sin*moveSpeed*time;

	std::cout << cos << "," << sin << std::endl;

	worldRect.x += xSpeed;
	worldRect.y += ySpeed;
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