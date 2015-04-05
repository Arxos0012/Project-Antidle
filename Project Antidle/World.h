#ifndef WORLD_H
#define WORLD_H

#include <SDL.h>
#include <array>
#include <iostream>
#include <map>

class Player;
class Ability;

class World{
public:
	World(int width, int height, int screenWidth, int screenHeight);
	int getWidth();
	int getHeight();

	SDL_Rect* getMapRect();

	void update(Player& player);

	void addAbility(Ability &ability);
	void removeAbility(std::string &name);

	Ability* getAbility(std::string &name);

	std::map<std::string, Ability>* getAbilities();

private:
	int screenWidth, screenHeight;
	SDL_Rect mapRect;
	float buffercoords;
	std::map<std::string, Ability> abilities;
};

#endif