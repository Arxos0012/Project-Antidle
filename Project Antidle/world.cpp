#include "World.h"
#include<iostream>

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

void World::coordWorldToScreen(int* coords, float* player, int width, int height, int screenWidth, int screenHeight){
	coords[0] += (screenWidth - width) /2 - player[0];
	coords[1] += (screenHeight - height) / 2 - player[1];
}

void World::coordScreenToWorld(int* coords, int width, int height, int screenWidth, int screenHeight){
	coords[0] -= (screenWidth + width) / 2;
	coords[1] -= (screenWidth + height) / 2;
}

void World::setX(int x){
	mapRect.x = x;
}

void World::setY(int y){
	mapRect.y = y;
}