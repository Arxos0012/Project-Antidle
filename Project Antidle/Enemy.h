#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "player.h"

class Enemy : public Entity{
public:
	void update(Player &player);

	void render(SDL_Renderer* renderer);

	void move(Player &player, float time);

	Enemy(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, Player &player, std::string texturePath, std::string name = "generic enemy") : Entity(renderer, x, y, screenWidth, screenHeight, texturePath, name){
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