#ifndef ABILITY_H
#define ABILITY_H

#include <SDL.h>

class Ability{
public:
	Ability(int x = 0, int y = 0);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	SDL_Rect* getRect();
private:
	SDL_Rect rect;
};

#endif