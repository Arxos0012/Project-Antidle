#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "player.h"

class Enemy : public Entity{
public:
	void update(Player &player){
		screenRect.x = (screenWidth / 2 + worldRect.x) - player.getX() - worldRect.w / 2;
		screenRect.y = (screenHeight / 2 + worldRect.y) - player.getY() - worldRect.h / 2;
	}

	void move(Player &player, float time);

	Enemy(int x, int y, int w, int h, int screenWidth, int screenHeight, Player &player, std::string name = "generic enemy") : Entity(x, y, w, h, screenWidth, screenHeight, name){
		this->type = ENEMY;
		update(player);
		this->x = x;
		this->y = y;
	}

private:
	const int MOVESPEED = 100;
	float x, y;
};
#endif