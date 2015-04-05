#include "World.h"
#include "player.h"

World::World(int width, int height, int screenWidth, int screenHeight){
	mapRect.w = width;
	mapRect.h = height;
	mapRect.x = (screenWidth - mapRect.w) / 2;
	mapRect.y = (screenHeight - mapRect.h) / 2;

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

SDL_Rect* World::getMapRect(){
	return &mapRect;
}

int World::getWidth(){
	return mapRect.w;
}

int World::getHeight(){
	return mapRect.h;
}

void World::update(Player& player){
	mapRect.x = (screenWidth - mapRect.w) / 2 - player.getX();
	mapRect.y = (screenHeight - mapRect.h) / 2 - player.getY();

	std::map<std::string, Ability>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		it->second.update(player.getX(), player.getY());
	}
}


void World::addAbility(Ability &ability){
	std::map<std::string, Ability>::iterator it = abilities.begin();
	abilities.insert(it, std::pair<std::string, Ability>(ability.getName(), ability));
}

void World::removeAbility(std::string &name){
	std::map<std::string, Ability>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->first == name){
			abilities.erase(it);
			return;
		}
	}
}

Ability* World::getAbility(std::string &name){
	std::map<std::string, Ability>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->first == name) return &(it->second);
	}
	return NULL;
}

std::map<std::string, Ability>* World::getAbilities(){
	return &abilities;
}