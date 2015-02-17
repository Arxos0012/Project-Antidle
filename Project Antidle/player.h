#ifndef PLAYER_H
#define PLAYER_h

#include <SDL_timer.h>

class Player{
public:
	Player();
	void move();
	int getX();
	int getY();
private:
	int playerX, playerY;
	const int MOVE_SPEED = 80;
	Uint32 lastTime, currentTime;
	float timePassed;
};

#endif