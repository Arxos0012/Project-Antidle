#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <map>
#include <vector>
#include "ability.h"
#include "controls.h"
#include "static.h"
#include "projectile.h"

class Player : public Entity{
public:
	Player(SDL_Renderer* renderer, int x, int y, int worldWidth, int worldHeight, int screenWidth, int screenHeight, std::string texturePath, std::string name = "generic player") : Entity(renderer, x, y, screenWidth, screenHeight, texturePath, name){
		screenRect.x = (screenWidth - screenRect.w) / 2;
		screenRect.y = (screenHeight - screenRect.h) / 2;
		this->worldWidth = worldWidth;
		this->worldHeight = worldHeight;
		this->type = PLAYER;
	}

	void setControls(Controls &controls){ this->controls = controls; }

	//different from other update functions, checks for keyboard inputs
	void update(SDL_Renderer* renderer, float time, std::vector<Static*>& stats);
	
	void render(SDL_Renderer* renderer);

	void setX(int x);
	void setY(int y);
	
	int numberOfAbilites(){ return abilities.size(); }

	void addAbility(Ability* ability);
	void removeAbiltiy(std::string &name);

	std::map<std::string, Projectile*> getFiredProjectiles();

	Ability* getAbility(std::string &name);

private:
	Controls controls;
	int worldWidth, worldHeight;
	float x = 0, y = 0;
	const int MOVESPEED = 500;	//pixels per second
	const int ICON_SPACING = 10;	//pixles
	std::map<std::string, Ability*> abilities;	
	Ability* primeAbilities[2];

	void moveLeft(float time);
	void moveRight(float time);
	void moveUp(float time);
	void moveDown(float time);

	void untouch(Static* stat, float time);
	void triggerAbility(Ability* ability, SDL_Renderer* renderer, int* info);
};

#endif