#ifndef ABILITY_H
#define ABILITY_H

#include <SDL.h>
#include <array>

class Ability{
public:
	const static enum actions{
		TEST_ABILITY
	};

	Ability(int x = 0, int y = 0);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	int getWidth();
	int getHeight();
	SDL_Rect* getWorldRect();
	SDL_Rect* getScreenRect(){
		return &screenRect;
	}
	void setScreenRect(int* coords){
		screenRect.x = coords[0];
		screenRect.y = coords[2];
	}
	int* getCoords(){
		return coords;
	}
private:
	void updateCoords();
	int coords[2];
	SDL_Rect worldRect;
	SDL_Rect screenRect;
};

#endif