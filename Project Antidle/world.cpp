#include "World.h"
#include "player.h"

World::World(int width, int height, int screenWidth, int screenHeight){
	mapRect.w = width;
	mapRect.h = height;
	mapRect.x = (screenWidth - mapRect.w) / 2;
	mapRect.y = (screenHeight - mapRect.h) / 2;

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

SDL_Rect* World::getMapRect(){
	return &mapRect;
}

int World::getWidth(){
	return mapRect.w;
}

int World::getHeight(){
	return mapRect.h;
}

void World::coordWorldToScreen(int* coords, float* player, int width, int height, int screenWidth, int screenHeight){
	coords[0] += (screenWidth - width) /2 - player[0];
	coords[1] += (screenHeight - height) / 2 - player[1];
}

void World::coordScreenToWorld(int* coords, int width, int height, int screenWidth, int screenHeight){
	coords[0] -= (screenWidth + width) / 2;
	coords[1] -= (screenWidth + height) / 2;
}

void World::update(Player& player){
	mapRect.x = (screenWidth - mapRect.w) / 2 - player.getX();
	mapRect.y = (screenHeight - mapRect.h) / 2 - player.getY();
}