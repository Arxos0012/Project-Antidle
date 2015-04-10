#ifndef PROJECTILE_H
#define PROJECTILE_H

#define _USE_MATH_DEFINES

#include "Object.h"
#include <cmath>

class Projectile : public Object{
public:
	void render(SDL_Renderer* renderer){
		SDL_Point center = { screenRect.x + screenRect.w / 2, screenRect.y + screenRect.h / 2 };
		texture.render(screenRect.x, screenRect.y, renderer, NULL, direction, &center);
	}

	void update(Player &player, float time){
		move(time);
		screenRect.x = (screenWidth / 2 + center.x) - player.getX() - screenRect.w / 2;
		screenRect.y = (screenHeight / 2 + center.y) - player.getY() - screenRect.h / 2;
	}

	//NOTE: Direction is measured in degrees
	Projectile(SDL_Renderer* renderer, int x, int y, float direction, int screenWidth, int screenHeight, Player &player, std::string texturePath, std::string name = "generic object") : Object(renderer, x, y, screenWidth, screenHeight, player, texturePath, name){
		this->objectType = PROJECTILE;
		this->direction = direction;
		this->x = x;
		this->y = y;
	}
private:
	void move(float time){
		x += time*MOVESPEED*std::cos(direction*DEGREES_TO_RADIANS);
		y += time*MOVESPEED*std::sin(direction*DEGREES_TO_RADIANS);

		center.x = (int)x;
		center.y = (int)y;
	}

	float x, y;

	float DEGREES_TO_RADIANS = (2 * M_PI) / 260.0;
	int MOVESPEED = 100;
	float direction;
};

#endif