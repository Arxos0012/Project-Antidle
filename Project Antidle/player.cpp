#include "player.h"

void Player::setX(int x){
	if (abs(x) > (worldWidth - worldRect.w) / 2){
		if (worldRect.x > 0) worldRect.x = (worldWidth - worldRect.w) / 2;
		else worldRect.x = (-worldWidth + worldRect.w) / 2;
	}
	else worldRect.x = x;
}

void Player::setY(int y){
	if (abs(y) > (worldHeight - worldRect.h) / 2){
		if (worldRect.y > 0) worldRect.y = (worldHeight - worldRect.h) / 2;
		else worldRect.y = (-worldHeight + worldRect.h) / 2;
	}
	else worldRect.y = y;
}

void Player::moveLeft(int worldWidth, float time){
	x -= MOVESPEED*time;
	if (x < (-worldWidth + worldRect.w) / 2) x = (-worldWidth + worldRect.w) / 2;
	worldRect.x = (int)x;
}

void Player::moveRight(int worldWidth, float time){
	x += MOVESPEED*time;
	if (x >(worldWidth - worldRect.w) / 2) x = (worldWidth - worldRect.w) / 2;
	worldRect.x = (int)x;
}

void Player::moveUp(int worldHeight, float time){
	y -= MOVESPEED*time;
	if (y < (-worldHeight + worldRect.h) / 2) y = (-worldHeight + worldRect.h) / 2;
	worldRect.y = (int)y;
}

void Player::moveDown(int worldHeight, float time){
	y += MOVESPEED*time;
	if (y >(worldHeight - worldRect.h) / 2) y = (worldHeight - worldRect.h) / 2;
	worldRect.y = (int)y;
}