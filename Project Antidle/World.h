#ifndef WORLD_H
#define WORLD_H

#include <SDL.h>
#include <array>
#include <iostream>
#include <map>
#include <vector>
#include "static.h"

class Player;
class Ability;

class World{
public:
	World(int width, int height, int screenWidth, int screenHeight);
	int getWidth();
	int getHeight();

	SDL_Rect* getMapRect();

	void render(SDL_Renderer* renderer);
	void update(Player& player);

	void addStatic(Static* stat);

	void addAbility(Ability* ability);
	void removeAbility(std::string &name);

	Ability* getAbility(std::string &name);

	std::map<std::string, Ability*>* getAbilities();

	std::vector<Static*> getOnScreenStatics();

private:
	int screenWidth, screenHeight;
	SDL_Rect mapRect;
	float buffercoords;
	std::map<std::string, Ability*> abilities;
	std::map<std::string, Static*> statics;

	bool onScreen(Static* stat);
};

#endif