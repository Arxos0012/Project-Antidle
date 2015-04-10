#ifndef ABILITY_H
#define ABILITY_H

#include "entity.h"

class Ability : public Entity{
public:
	void update(int playerX, int playerY){
		screenRect.x = (screenWidth / 2 + center.x) - playerX;
		screenRect.y = (screenHeight / 2 + center.y) - playerY;
	}

	void render(SDL_Renderer* renderer){
		SDL_Point center = { screenRect.x + screenRect.w / 2, screenRect.y + screenRect.h / 2 };
		texture.render(screenRect.x, screenRect.y, renderer, NULL, 0, &center);
	}

	void markAsPlayerOwned(){ playerOwned = true; }

	void setKey(int scanCode){ keyScanCode = scanCode; }

	void performAction(){ std::cout << "Doin' my thang!!!\n"; }

	int getScanCode(){ return keyScanCode; }

	Ability(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, int playerX, int playerY, std::string texturePath, std::string name = "generic ability") : Entity(renderer, x, y, screenWidth, screenHeight, texturePath, name){
		this->type = ABILITY;
		update(playerX, playerY);
	}
private:
	bool playerOwned = false;
	int keyScanCode;
};

#endif