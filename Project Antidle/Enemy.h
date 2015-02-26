#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>

class Enemy{
public:
	Enemy(int x, int y);
	int* getCoords();
	void move(int target[]);
private:
	SDL_Rect rect;
	int moveSpeed;
};

#endif