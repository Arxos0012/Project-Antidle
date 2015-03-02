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
	SDL_Rect* getRect();
	std::array<int, 2> const & getCoords(){
		return coords;
	}
private:
	void updateCoords();
	std::array<int, 2> coords;
	SDL_Rect rect;
};

#endif