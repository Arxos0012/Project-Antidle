#ifndef ENTITY_H
#define ENTIIY_H

#include <SDL.h>
#include <string>
#include <iostream>

#pragma once

class Entity{
public:
	Entity(int x, int y, int w, int h, int screenWidth, int screenHeight, std::string name = "generic entity"){
		worldRect.x = x;
		worldRect.y = y;
		worldRect.w = screenRect.w = w;
		worldRect.h = screenRect.h = h;
		this->name = name;
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
	}

	int getX(){ return worldRect.x; }
	int getY(){ return worldRect.y; }
	
	virtual void setX(){};		//set world x coord and updates screen coords
	virtual void setY(){};		//set world y coord and updates screen coords

	const SDL_Rect* getWorldRect() { return &worldRect; }
	const SDL_Rect* getScreenRect() { return &screenRect; }

	std::string getName(){ return name; }				//return name of entity
	int getType(){ return type; }						//return type of entity

protected:
	SDL_Rect worldRect, screenRect;
	std::string name;
	int type, screenWidth, screenHeight;
	enum Types{
		PLAYER, ENEMY, ABILITY, OBJECT, PROJECTILE
	};
};

#endif