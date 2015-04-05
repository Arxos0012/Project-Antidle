#ifndef ABILITY_H
#define ABILITY_H

#include "entity.h"

class Ability : public Entity{
public:
	void update(int playerX, int playerY){
		screenRect.x = (screenWidth / 2 + worldRect.x) - playerX;
		screenRect.y = (screenHeight / 2 + worldRect.y) - playerY;
	}

	Ability(int x, int y, int w, int h, int screenWidth, int screenHeight, int playerX, int playerY, std::string name = "generic ability") : Entity(x, y, w, h, screenWidth, screenHeight, name){
		this->type = ABILITY;
		update(playerX, playerY);
	}
private:
	
};

#endif