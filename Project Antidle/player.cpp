#include "player.h"

Player::Player(){
	playerX = 0;
	playerY = 0;
	lastTime = SDL_GetTicks();
}

int Player::getX(){
	return playerX;
}

int Player::getY(){
	return playerY;
}

void Player::move(){
	currentTime = SDL_GetTicks();
	timePassed = (currentTime - lastTime) / 1000.0;
	lastTime = currentTime;
}

