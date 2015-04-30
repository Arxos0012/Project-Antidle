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

void World::render(SDL_Renderer* renderer){
	std::map<std::string, Ability*>::iterator at;
	for (at = abilities.begin(); at != abilities.end(); at++){
		at->second->render(renderer);
	}

	std::map<std::string, Static*>::iterator st;
	for (st = statics.begin(); st != statics.end(); st++){
		st->second->render(renderer);
	}
}

void World::update(Player& player){
	mapRect.x = (screenWidth - mapRect.w) / 2 - player.getX();
	mapRect.y = (screenHeight - mapRect.h) / 2 - player.getY();

	std::map<std::string, Ability*>::iterator at;
	for (at = abilities.begin(); at != abilities.end(); at++){
		at->second->update(player.getX(), player.getY());
	}

	std::map<std::string, Static*>::iterator st;
	for (st = statics.begin(); st != statics.end(); st++){
		st->second->update(player.getX(), player.getY());
	}
}


void World::addStatic(Static* stat){
	std::cout << "adding " << stat->getName() << " to world\n";
	std::map<std::string, Static*>::iterator it = statics.begin();
	statics.insert(it, std::pair<std::string, Static*>(stat->getName(), stat));
}

void World::addAbility(Ability* ability){
	std::cout << "adding " << ability->getName() << " to world\n";
	std::map<std::string, Ability*>::iterator it = abilities.begin();
	abilities.insert(it, std::pair<std::string, Ability*>(ability->getName(), ability));
}

void World::removeAbility(std::string &name){
	std::map<std::string, Ability*>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->first == name){
			abilities.erase(it);
			return;
		}
	}
}

Ability* World::getAbility(std::string &name){
	std::map<std::string, Ability*>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->first == name) return it->second;
	}
	return NULL;
}

std::map<std::string, Ability*>* World::getAbilities(){
	return &abilities;
}

std::vector<Static*> World::getOnScreenStatics(){
	std::vector<Static*> onScreens;

	std::map<std::string, Static*>::iterator st;
	for (st = statics.begin(); st != statics.end(); st++){
		if (onScreen(st->second)){
			onScreens.push_back(st->second);
		}
	}

	return onScreens;
}

bool World::onScreen(Static* stat){
	bool inXBound = (stat->getX() >= 0) && (stat->getX() <= screenWidth);
	bool inYBound = (stat->getY() >= 0) && (stat->getY() <= screenHeight);

	return inXBound && inYBound;
}