#ifndef WORLD_H
#define WORLD_H

#include <SDL.h>
#include <array>
#include "player.h"

class World{
public:
	World(int width, int height, int screenWidth, int screenHeight);
	int getWidth();
	int getHeight();

	void coordWorldToScreen(int* coords, float* player, int width, int height, int screenWidth, int screenHeight);
	void coordScreenToWorld(int* coords, int width, int height, int screenWidth, int screenHeight);

	SDL_Rect* getMapRect();

	void update(Player& player);
private:
	int screenWidth, screenHeight;
	SDL_Rect mapRect;
	float buffercoords;
};

#endif