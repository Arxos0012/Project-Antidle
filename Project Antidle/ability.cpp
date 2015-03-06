#include "ability.h"

using namespace std;

Ability::Ability(int x, int y){
	worldRect.x = x;
	worldRect.y = y;
	worldRect.w = 10;
	worldRect.h = 10;

	screenRect.w = 10;
	screenRect.h = 10;
}

int Ability::getWidth(){
	return worldRect.w;
}

int Ability::getHeight(){
	return worldRect.h;
}

void Ability::getCoords(int* coords){
	coords[0] = worldRect.x;
	coords[1] = worldRect.y;
}

void Ability::refreshScreenCoords(int* coords){
	screenRect.x = coords[0];
	screenRect.y = coords[1];
}

SDL_Rect* Ability::getScreenRect(){
	return &screenRect;
}