#ifndef WORLD_H
#define WORLD_H

#include <SDL.h>

class World{
public:
	World(int width, int height);
	int getWidth();
	int getHeight();

	void coordWorldToScreen(float coords[], int screenWidth, int screenHeight);
	void coordScreenToWorld(float coords[], int screenWidth, int screenHeight);

	SDL_Rect* getMapRect();

	void setX(int x);
	void setY(int y);
private:
	SDL_Rect mapRect;
	float buffercoords;
};

#endif