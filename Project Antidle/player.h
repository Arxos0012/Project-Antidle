#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity{
public:
	Player(int x, int y, int w, int h, int worldWidth, int worldHeight, int screenWidth, int screenHeight, std::string name = "generic player") : Entity(x, y, w, h, name){
		screenRect.x = (screenWidth - w) / 2;
		screenRect.y = (screenHeight - h) / 2;
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		this->worldWidth = worldWidth;
		this->worldHeight = worldHeight;
		this->type = PLAYER;
	}
	void setX(int x);
	void setY(int y);

	void moveLeft(int worldWidth, float time);
	void moveRight(int worldWidth, float time);
	void moveUp(int worldHeight, float time);
	void moveDown(int worldHeight, float time);

private:
	int screenWidth, screenHeight, worldWidth, worldHeight;
	float x = 0, y = 0;
	const int MOVESPEED = 100;	//pixels per second
};

#endif