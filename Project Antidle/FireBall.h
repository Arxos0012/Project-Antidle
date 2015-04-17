#ifndef FIREBALL_H
#define FIREBALL_H

#include <map>
#include "ability.h"
#include "projectile.h"

class FireBall : public Ability{
public:
	FireBall(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, int playerX, int playerY)
		: Ability(renderer,x,y,screenWidth,screenHeight,playerX,playerY,"fireball_ability","Fireball Ability"){}

	void performAction(SDL_Renderer* renderer, int playerX, int playerY, int mouseX, int mouseY){

		float xChange = mouseX - playerX;
		float yChange = mouseY - playerY;
		
		double direction = std::atan(yChange / xChange) * TO_DEGREES;

		int playerCoords[] = { playerX, playerY };

		std::string name = "fireball " + std::to_string(projectiles.size());
		std::string filePath = "fireball.png";

		std::map<std::string, Projectile>::iterator it = projectiles.begin();
		projectiles.insert(it, std::pair<std::string, Projectile>(name, Projectile(playerCoords, 100, direction, renderer, playerX, playerY, screenWidth, screenHeight, filePath, name)));
	}

	void updateProjectiles(float time, int playerX, int playerY){
		std::map<std::string, Projectile>::iterator it;
		for (it = projectiles.begin(); it != projectiles.end(); it++){
			it->second.update(time, playerX, playerY);
		}
	}

	void renderProjectiles(SDL_Renderer* renderer){
		std::map<std::string, Projectile>::iterator it;
		for (it = projectiles.begin(); it != projectiles.end(); it++){
			it->second.render(renderer);
		}
	}

private:
	std::map<std::string, Projectile> projectiles;
};

#endif