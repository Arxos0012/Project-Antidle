#ifndef ENTITY_H
#define ENTIIY_H

#include <SDL.h>
#include <string>
#include <iostream>

#include "texture.h"

#pragma once

class Entity{
public:
	Entity(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, std::string texturePath, std::string name = "generic entity"){
		center.x = x;
		center.y = y;
		this->name = name;
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		if (!(texture.loadTexture(texturePath, renderer))) std::cerr << "Failed to load this texture: " << texturePath << "\n.";
		screenRect.w = texture.getWidth();
		screenRect.h = texture.getHeight();
	}

	~Entity(){
	}


	int getX(){ return center.x; }
	int getY(){ return center.y; }

	int getWidth(){ return screenRect.w; }
	int getHeight(){ return screenRect.h; }
	
	virtual void setX(int x){ center.x = x; }		//set world x coord and updates screen coords
	virtual void setY(int y){ center.y = y; }		//set world y coord and updates screen coords

	const SDL_Rect* getScreenRect() { return &screenRect; }

	std::string getName(){ return name; }				//return name of entity
	int getType(){ return type; }						//return type of entity

protected:
	Texture texture;
	SDL_Rect screenRect;
	SDL_Point center;
	std::string name;
	int type, screenWidth, screenHeight;
	enum Types{
		PLAYER, ENEMY, ABILITY, OBJECT
	};
};

#endif