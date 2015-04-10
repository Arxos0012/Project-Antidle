#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "player.h"

class Enemy : public Entity{
public:
	void update(Player &player, float time);

	void render(SDL_Renderer* renderer);

	Enemy(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, Player &player, std::string texturePath, std::string name = "generic enemy") : Entity(renderer, x, y, screenWidth, screenHeight, texturePath, name){
		this->type = ENEMY;
		update(player, 0);
		this->x = x;
		this->y = y;
	}

private:
	void move(Player &player, float time);
	const int MOVESPEED = 100;
	float x, y;
};
#endif