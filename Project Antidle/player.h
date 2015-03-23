#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player{
public:
	Player(int x, int y, int screenWidth, int screenHeight);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	int* getPlayerColor();
	void setPlayerColor(int color[]);
	void setMoveSpeed(int moveSpeed);
	int getMoveSpeed();
	int getWidth(){ return screenRect.w; }
	int getHeight(){ return screenRect.h; }

private:
	SDL_Rect worldRect;
	SDL_Rect screenRect;
	int color[] = { 0x00, 0xFF, 0x00 };
	int MOVE_SPEED = 500;
};

#endif