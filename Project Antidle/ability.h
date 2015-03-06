#ifndef ABILITY_H
#define ABILITY_H

#include <SDL.h>
#include <string>

class Ability{
public:
	const static enum actions{
		TEST_ABILITY
	};

	Ability(int x = 0, int y = 0);
	int getX(){ return worldRect.x; }
	int getY(){ return worldRect.y; }
	int getWidth();
	int getHeight();
	SDL_Rect* getScreenRect();
	void refreshScreenCoords(int* coords);
	void getCoords(int* coords);
	std::string name(){ return "hi there"; };
private:
	int coords[2];
	SDL_Rect worldRect;
	SDL_Rect screenRect;
};

#endif