#include "Enemy.h"

void Enemy::update(Player &player){
	screenRect.x = (screenWidth / 2 + center.x) - player.getX() - screenRect.w / 2;
	screenRect.y = (screenHeight / 2 + center.y) - player.getY() - screenRect.h / 2;
}

void Enemy::render(SDL_Renderer* renderer){
	SDL_Point center = { screenRect.x + screenRect.w / 2, screenRect.y + screenRect.h / 2 };
	texture.render(screenRect.x, screenRect.y, renderer, NULL, 0, &center);
}

void Enemy::move(Player &player, float time){
	float distance = sqrt(pow(x - player.getX(), 2) + pow(y - player.getY(), 2));
	if (distance <= screenRect.w/2) return;
	float cos = (player.getX() - x) / distance;
	float sin = (player.getY() - y) / distance;

	x += MOVESPEED*cos*time;
	y += MOVESPEED*sin*time;

	center.x = (int)x;
	center.y = (int)y;
}
