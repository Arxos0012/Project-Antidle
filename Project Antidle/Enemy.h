#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>

class Enemy{
public:
	Enemy(int x, int y);
	void getCoords(int* coords);	//world based coordinates
	void move(float* target, float time);
	SDL_Rect* getScreenRect();
	void refeshScreenCoords(int* coords);
	int getWidth(){ return worldRect.w; }
	int getHeight(){ return worldRect.h; }
private:
	SDL_Rect worldRect;
	SDL_Rect screenRect;
	int moveSpeed = 20;	//in pixels per second
	float timeCollected = 0;
};

#endif