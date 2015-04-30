#ifndef ABILITY_H
#define ABILITY_H
#define _USE_MATH_DEFINES

#include <cmath>
#include <map>
#include <string>
#include "entity.h"

class Ability : public Entity{
public:
	void update(int playerX, int playerY){
		screenRect.x = ((screenWidth / 2 + center.x) - screenRect.w / 2) - playerX;
		screenRect.y = ((screenHeight / 2 + center.y) - screenRect.h / 2) - playerY;
	}

	virtual void update(float time, int playerX, int playerY){}
	virtual void render(SDL_Renderer* renderer, int someKey){}

	void render(SDL_Renderer* renderer){
		SDL_Point center = { screenRect.x + screenRect.w / 2, screenRect.y + screenRect.h / 2 };
		texture.render(screenRect.x, screenRect.y, renderer, NULL, 0, &center);
	}

	void renderIcon(SDL_Renderer* renderer, int x, int y){
		icon.render(x, y, renderer);
	}

	void markAsPlayerOwned(){ playerOwned = true; }

	void setKey(int scanCode){ keyScanCode = scanCode; }

	virtual void performAction(){}
	virtual void performAction(SDL_Renderer* renderer, int playerX, int playerY, int mouseX, int mouseY){}

	int getScanCode(){ return keyScanCode; }

	Ability(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, int playerX, int playerY, std::string iconPath, std::string name = "generic ability") : Entity(renderer, x, y, screenWidth, screenHeight, "ability_token.png", name){
		this->type = ABILITY;
		icon.loadTexture(iconPath, renderer);
		update(playerX, playerY);
	}

	int getIconWidth(){ return icon.getWidth(); }
	int getIconHeight(){ return icon.getHeight(); }

private:
	bool playerOwned = false;
	int keyScanCode;
protected:
	Texture icon;
	float TO_DEGREES = 180 / M_PI;
};

#endif