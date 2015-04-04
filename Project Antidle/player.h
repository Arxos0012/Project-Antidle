#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <map>
#include "ability.h"
#include "keyboard.h"

class Player : public Entity{
public:
	Player(int x, int y, int w, int h, int worldWidth, int worldHeight, int screenWidth, int screenHeight, std::string name = "generic player") : Entity(x, y, w, h, screenWidth, screenHeight, name){
		screenRect.x = (screenWidth - w) / 2;
		screenRect.y = (screenHeight - h) / 2;
		this->worldWidth = worldWidth;
		this->worldHeight = worldHeight;
		this->type = PLAYER;
	}

	void setKeyboard(Keyboard &keyboard){ this->keyboard = keyboard;  }

	//different from other update functions, checks for keyboard inputs
	void update(float time);

	void setX(int x);
	void setY(int y);
	
	int numberOfAbilites(){ return abilities.size(); }

	void addAbility(Ability &ability);
	void removeAbiltiy(std::string &name);

	Ability* getAbiltiy(std::string &name);

private:
	Keyboard keyboard;
	int worldWidth, worldHeight;
	float x = 0, y = 0;
	const int MOVESPEED = 500;	//pixels per second
	std::map<std::string, Ability> abilities;

	void moveLeft(float time);
	void moveRight(float time);
	void moveUp(float time);
	void moveDown(float time);
};

#endif