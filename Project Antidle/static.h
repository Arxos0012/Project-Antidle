#ifndef	STATIC_H
#define STATIC_H

#include "Object.h"

class Static : public Object{
public:
	
	void update(int playerX, int playerY){
		screenRect.x = ((center.x - screenRect.w / 2) + screenWidth / 2) - playerX;
		screenRect.y = ((center.y - screenRect.h / 2) + screenHeight / 2) - playerY;
	}

	Static(SDL_Renderer* renderer, int x, int y, int playerX, int playerY, int screenWidth, int screenHeight, std::string texturePath, std::string name = "generic static") : Object(renderer, x, y, screenWidth, screenHeight, texturePath, name){
		this->objectType = STATIC;
		update(playerX, playerY);
	}
	int getWidth(){ return screenRect.w; }
	int getHeight(){ return screenRect.h; }

private:
protected:
};

#endif