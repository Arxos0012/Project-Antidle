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

		x += xChange;
		y += yChange;

		center.x = (int)x;
		center.y = (int)y;

		screenRect.x = (screenWidth / 2 + center.x) - playerX;
		screenRect.y = (screenHeight / 2 + center.y) - playerY;
	}

	Projectile(int* playerCoords, int moveSpeed, double direction, SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, std::string texturePath, std::string name = "generic projectile")
		: Object(renderer,x,y,screenWidth,screenHeight,texturePath,name){
		this->objectType = PROJECTILE;
		this->direction = direction;
		this->moveSpeed = moveSpeed;
		this->x = x;
		this->y = y;
		update(0, playerCoords[0], playerCoords[1]);
	}

	int getScreenX(){ 
		return screenRect.x;
		std::cout << "X is set.\n";
	}
	int getScreenY(){
		return screenRect.y;
		std::cout << "Y is set.\n";
	}

	bool getCanRender(){ return canRender; }

	void setDirection(double direction){ this->direction = direction; }
	void setCanRender(bool canRender){ this->canRender = canRender; }

private:
	int moveSpeed;
	bool canRender = true;
	float x, y;
	const float TO_RADIANS = M_PI / 180;
};

#endif