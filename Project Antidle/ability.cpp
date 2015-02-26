#include "ability.h"

Ability::Ability(int x, int y){
	rect.x = x;
	rect.y = y;
	rect.w = 10;
	rect.h = 10;
}

int Ability::getX(){
	return rect.x;
}

int Ability::getY(){
	return rect.y;
}

void Ability::setX(int x){
	rect.x = x;
}

void Ability::setY(int y){
	rect.y = y;
}

int Ability::getWidth(){
	return rect.w;
}

int Ability::getHeight(){
	return rect.h;
}

SDL_Rect* Ability::getRect(){
	return &rect;
}