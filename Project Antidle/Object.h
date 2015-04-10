#ifndef OBJECT_H
#define OBJECT_H

#include "entity.h"
#include "player.h"

class Object : public Entity{
public:
	virtual void update(Player &player){
		screenRect.x = (screenWidth / 2 + center.x) - player.getX() - screenRect.w / 2;
		screenRect.y = (screenHeight / 2 + center.y) - player.getY() - screenRect.h / 2;
	}

	virtual void render(SDL_Renderer* renderer){
		SDL_Point center = { screenRect.x + screenRect.w / 2, screenRect.y + screenRect.h / 2 };
		texture.render(screenRect.x, screenRect.y, renderer, NULL, 0, &center);
	}

	Object(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, Player &player, std::string texturePath, std::string name = "generic object") : Entity(renderer,x,y,screenWidth,screenHeight,texturePath,name){
		this->type = OBJECT;
		update(player);
	}
private:
protected:
	int objectType;
	enum ObjectTypes{
		PROJECTILE, STATIC
	};
};

#endif