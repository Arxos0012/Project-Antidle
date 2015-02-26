#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <SDL_timer.h>

class Enemy{
public:
	Enemy(int x, int y);
	int* getCoords();
	void move(int target[]);
	SDL_Rect* getRect();
private:
	SDL_Rect rect;
	int moveSpeed;	//in pixels per second
	Uint32 lastTime;
	Uint32 currentTime;
	int coordBuffer[2];
	void refreshCoordBuffer(int x, int y);
};

#endif