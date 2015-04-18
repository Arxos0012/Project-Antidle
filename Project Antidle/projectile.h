#ifndef PROJECTILE_H
#define PROJECTILE_H

#define _USE_MATH_DEFINES

#include <math.h>
#include "Object.h"

class Projectile : public Object{
public:
	void update(float time, int playerX, int playerY){
		float xChange = std::cos(direction * TO_RADIANS)*moveSpeed*time;
		float yChange = std::sin(direction * TO_RADIANS)*moveSpeed*time;

		center.x += xChange;
		center.y += yChange;

		screenRect.x = ((screenWidth / 2 + center.x) - screenRect.w / 2) - playerX;
		screenRect.y = ((screenHeight / 2 + center.y) - screenRect.h / 2) - playerY;
	}

	Projectile(int* playerCoords, float moveSpeed, double direction, SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, std::string texturePath, std::string name = "generic projectile")
		: Object(renderer,x,y,screenWidth,screenHeight,texturePath,name){
		this->direction = direction;
		this->moveSpeed = moveSpeed;
		update(0, playerCoords[0], playerCoords[1]);
	}
private:
	float moveSpeed;
	const float TO_RADIANS = M_PI / 180;
};

#endif