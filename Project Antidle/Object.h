#ifndef OBJECT_H
#define OBJECT_H

#include "entity.h"
#include "player.h"

class Object : public Entity{
public:
	void update(Player &player);

	void render(SDL_Renderer* renderer){
		texture.render(screenRect.x, screenRect.y, renderer, NULL, 0, &center);
	}

	Object(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, Player &player, std::string texturePath, std::string name = "generic object") : Entity(renderer,x,y,screenWidth,screenHeight,texturePath,name){
		this->type = OBJECT;
		update(player);
	}
private:
protected:
	enum ObjectTypes{
		PROJECTILE, STATIC
	};
};

#endif