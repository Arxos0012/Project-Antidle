#ifndef ABILITY_H
#define ABILITY_H

#include "entity.h"

class Ability : public Entity{
public:
	Ability(int x, int y, int w, int h, std::string name = "generic ability") : Entity(x, y, w, h, name){
		this->type = ABILITY;
	}
private:
	
};

#endif