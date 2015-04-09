#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <map>
#include "ability.h"
#include "keyboard.h"

class Player : public Entity{
public:
	Player(SDL_Renderer* renderer, int x, int y, int worldWidth, int worldHeight, int screenWidth, int screenHeight, std::string texturePath, std::string name = "generic player") : Entity(renderer, x, y, screenWidth, screenHeight, texturePath, name){
		screenRect.x = (screenWidth - screenRect.w) / 2;
		screenRect.y = (screenHeight - screenRect.h) / 2;
		this->worldWidth = worldWidth;
		this->worldHeight = worldHeight;
		this->type = PLAYER;
	}

	void setKeyboard(Keyboard &keyboard){ this->keyboard = keyboard;  }

	//different from other update functions, checks for keyboard inputs
	void update(float time);
	
	void render(SDL_Renderer* renderer);

	void setX(int x);
	void setY(int y);
	
	int numberOfAbilites(){ return abilities.size(); }

	void addAbility(Ability* ability);
	void removeAbiltiy(std::string &name);

	Ability* getAbility(std::string &name);

private:
	Keyboard keyboard;
	int worldWidth, worldHeight;
	float x = 0, y = 0;
	const int MOVESPEED = 500;	//pixels per second
	std::map<std::string, Ability*> abilities;

	void moveLeft(float time);
	void moveRight(float time);
	void moveUp(float time);
	void moveDown(float time);
};

#endif