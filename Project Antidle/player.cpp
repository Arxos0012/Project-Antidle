#include "player.h"

void Player::setX(int x){
	if (abs(x) > (worldWidth - screenRect.w) / 2){
		if (center.x > 0) center.x = (worldWidth - screenRect.w) / 2;
		else center.x = (-worldWidth + screenRect.w) / 2;
	}
	else center.x = x;
}

void Player::setY(int y){
	if (abs(y) > (worldHeight - screenRect.h) / 2){
		if (center.y > 0) center.y = (worldHeight - screenRect.h) / 2;
		else center.y = (-worldHeight + screenRect.h) / 2;
	}
	else center.y = y;
}

void Player::moveLeft(float time){
	x -= MOVESPEED*time;
	if (x < (-worldWidth + screenRect.w) / 2) x = (-worldWidth + screenRect.w) / 2;
	center.x = (int)x;
}

void Player::moveRight(float time){
	x += MOVESPEED*time;
	if (x >(worldWidth - screenRect.w) / 2) x = (worldWidth - screenRect.w) / 2;
	center.x = (int)x;
}

void Player::moveUp(float time){
	y -= MOVESPEED*time;
	if (y < (-worldHeight + screenRect.h) / 2) y = (-worldHeight + screenRect.h) / 2;
	center.y = (int)y;
}

void Player::moveDown(float time){
	y += MOVESPEED*time;
	if (y >(worldHeight - screenRect.h) / 2) y = (worldHeight - screenRect.h) / 2;
	center.y = (int)y;
}

void Player::addAbility(Ability* ability){
	std::map<std::string, Ability*>::iterator it = abilities.begin();
	abilities.insert(it, std::pair<std::string, Ability*>(ability->getName(), ability));
	abilities.at(ability->getName())->markAsPlayerOwned();
}

void Player::removeAbiltiy(std::string &name){
	std::map<std::string, Ability*>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->first == name){
			abilities.erase(it);
			return;
		}
	}
}

Ability* Player::getAbility(std::string &name){
	std::map<std::string, Ability*>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->first == name) return it->second;
	}
	return NULL;
}

void Player::update(SDL_Renderer* renderer, float time){
	controls.update();

	if (controls.getKeyState(SDL_SCANCODE_W)) moveUp(time);
	if (controls.getKeyState(SDL_SCANCODE_S)) moveDown(time);
	if (controls.getKeyState(SDL_SCANCODE_A)) moveLeft(time);
	if (controls.getKeyState(SDL_SCANCODE_D)) moveRight(time);
}

void Player::render(SDL_Renderer* renderer){
	SDL_Point center = { screenWidth / 2, screenHeight / 2 };
	texture.render(screenRect.x, screenRect.y, renderer, NULL, 0, &center);
}