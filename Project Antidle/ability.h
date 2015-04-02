#ifndef ABILITY_H
#define ABILITY_H

#include "player.h"

class Ability : public Entity{
public:
	void update(Player &player){
		screenRect.x = (screenWidth / 2 + worldRect.x) - player.getX();
		screenRect.y = (screenHeight / 2 + worldRect.y) - player.getY();
	}

	Ability(int x, int y, int w, int h, int screenWidth, int screenHeight, Player &player, std::string name = "generic ability") : Entity(x, y, w, h, screenWidth, screenHeight, name){
		this->type = ABILITY;
		update(player);
	}
private:
	
};

#endif