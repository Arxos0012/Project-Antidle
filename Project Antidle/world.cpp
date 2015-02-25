#include "World.h"

World::World(int width, int height){
	mapRect.w = width;
	mapRect.h = height;
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

void World::coordWorldToScreen(float* coords, int screenWidth, int screenHeight){
	coords[0] = screenWidth / 2 - coords[0];
	coords[0] = screenHeight / 2 - coords[1];
}

void World::coordScreenToWorld(float* coords, int screenWidth, int screenHeight){
	coords[0] = coords[0] - screenWidth / 2;
	coords[1] = coords[1] - screenHeight / 2;
}

void World::setX(int x){
	mapRect.x = x;
}

void World::setY(int y){
	mapRect.y = y;
}