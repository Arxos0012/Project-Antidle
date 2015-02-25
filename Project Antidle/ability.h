#ifndef ABILITY_H
#define ABILITY_H

#include <SDL.h>

class Ability{
public:
	friend enum actions{
		TEST_ABILITY
	};

	Ability(int x = 0, int y = 0);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	int getWidth();
	int getHeight();
private:
	SDL_Rect rect;
};

#endif