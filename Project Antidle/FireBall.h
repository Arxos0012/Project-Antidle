#ifndef FIREBALL_H
#define FIREBALL_H

#include "ability.h"
#include

class FireBall : public Ability{
public:
	FireBall(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, int playerX, int playerY, std::string texturePath, std::string name = "fireball")
		: Ability(renderer,x,y,screenWidth,screenHeight,playerX,playerY,texturePath,name){}

	void performAction(){
	
	}
private:
};

#endif