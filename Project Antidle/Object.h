#ifndef OBJECT_H
#define OBJECT_H

#include "entity.h"

class Object : public Entity{
public:
	enum ObjectType{
		PROJECTILE, STATIC, AURA
	};

	Object(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, std::string texturePath, std::string name = "generic object")
		: Entity(renderer, x, y, screenWidth, screenHeight, texturePath, name){
		this->type = OBJECT;
	}

	void render(SDL_Renderer* renderer){
		SDL_Point point = { screenRect.x + (screenWidth/2), screenRect.y + (screenHeight/2)};
		texture.render(screenRect.x, screenRect.y, renderer, NULL, direction);
	}

protected:
	//directions are measured in degrees
	double direction = 0;
	int objectType;
	/*Projectile - updates based on: movement, player position
	  Static	 - updates based on: player position
	  Aura		 - updates based on: player position (moving with the player)
	*/
};

#endif