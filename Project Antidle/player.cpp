#include "player.h"

Player::Player(int x, int y, int screenWidth, int screenHeight){
	worldRect.x = x; 
	worldRect.y = y;
	worldRect.w = 50;
	worldRect.h = 50;

	screenRect.x = screenWidth / 2 - 25;
	screenRect.y = screenHeight / 2 - 25;
	screenRect.w = 50;
	screenRect.h = 50;
	
}

void Player::setX(int x){
	worldRect.x = x
}

void Player::setY(int y){
	worldRect.y = y;
}

int Player::getX(){
	return worldRect.x;
}

int Player::getY(){
	return worldRect.y;
}

void Player::setMoveSpeed(int moveSpeed){
	MOVE_SPEED = moveSpeed;
}

int* Player::getPlayerColor(){
	return color;
}

void Player::setPlayerColor(int color[]){
	for (int i = 0; i < 3; i++) this->color[i] = color[i];
}

int Player::getMoveSpeed(){
	return MOVE_SPEED;
}