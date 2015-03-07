#include "ability.h"
#include <array>

using namespace std;

Ability::Ability(int x, int y){
	worldRect.x = x;
	worldRect.y = y;
	worldRect.w = 10;
	worldRect.h = 10;

	worldRect.w = 10;
	worldRect.h = 10;
}

int Ability::getX(){
	return worldRect.x;
}

int Ability::getY(){
	return worldRect.y;
}

void Ability::setX(int x){
	worldRect.x = x;
}

void Ability::setY(int y){
	worldRect.y = y;
}

int Ability::getWidth(){
	return worldRect.w;
}

int Ability::getHeight(){
	return worldRect.h;
}

SDL_Rect* Ability::getWorldRect(){
	return &worldRect;
}

void Ability::updateCoords(){
	coords[0] = worldRect.x;
	coords[1] = worldRect.y;
}