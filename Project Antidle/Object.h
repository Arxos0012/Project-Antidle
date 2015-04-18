#ifndef OBJECT_H
#define OBJECT_H

#include "entity.h"

class Object : public Entity{
public:
	Object(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, std::string texturePath, std::string name = "generic object")
		: Entity(renderer, x, y, screenWidth, screenHeight, texturePath, name){}

	void render(SDL_Renderer* renderer){
		SDL_Point center = { screenRect.x + screenRect.w / 2, screenRect.y + screenRect.h / 2 };
		texture.render(screenRect.x, screenRect.y, renderer, NULL, direction, &center);
	}

protected:
	//directions are measured in degrees
	double direction = 0;
	enum ObjectType{
		PROJECTILE, STATIC, AURA
	};
	/*Projectile - updates based on: movement, player position
	  Static	 - updates based on: player position
	  Aura		 - updates based on: player position (moving with the player)
	*/
};

#endif