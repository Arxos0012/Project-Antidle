#include "player.h"
#include "ability.h"

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

void Player::moveLeft(float time){
	x -= MOVESPEED*time;
	if (x < (-worldWidth + worldRect.w) / 2) x = (-worldWidth + worldRect.w) / 2;
	worldRect.x = (int)x;
}

void Player::moveRight(float time){
	x += MOVESPEED*time;
	if (x >(worldWidth - worldRect.w) / 2) x = (worldWidth - worldRect.w) / 2;
	worldRect.x = (int)x;
}

void Player::moveUp(float time){
	y -= MOVESPEED*time;
	if (y < (-worldHeight + worldRect.h) / 2) y = (-worldHeight + worldRect.h) / 2;
	worldRect.y = (int)y;
}

void Player::moveDown(float time){
	y += MOVESPEED*time;
	if (y >(worldHeight - worldRect.h) / 2) y = (worldHeight - worldRect.h) / 2;
	worldRect.y = (int)y;
}

void Player::addAbility(Ability ability){
	std::map<std::string, Ability>::iterator it = abilities.begin();
	abilities.insert(it, std::pair<std::string, Ability>(ability.getName(), ability));
}

void Player::removeAbiltiy(std::string name){
	std::map<std::string, Ability>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->first == name){
			abilities.erase(it);
			return;
		}
	}
}

Ability* Player::getAbiltiy(std::string name){
	std::map<std::string, Ability>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->first == name) return &(it->second);
	}
	return NULL;
}