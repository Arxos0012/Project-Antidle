#include "Enemy.h"
#include "player.h"

void Enemy::move(Player &player, float time){
	float distance = sqrt(pow(x - player.getX(), 2) + pow(y - player.getY(), 2));
	if (distance <= worldRect.w/2) return;
	float cos = (player.getX() - x) / distance;
	float sin = (player.getY() - y) / distance;

	x += MOVESPEED*cos*time;
	y += MOVESPEED*sin*time;

	worldRect.x = (int)x;
	worldRect.y = (int)y;
}
