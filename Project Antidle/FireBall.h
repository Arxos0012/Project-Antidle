#ifndef FIREBALL_H
#define FIREBALL_H

#include <map>
#include "ability.h"
#include "projectile.h"

class FireBall : public Ability{
public:
	FireBall(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, int playerX, int playerY, std::string iconPath)
		: Ability(renderer,x,y,screenWidth,screenHeight,playerX,playerY, iconPath, "Fireball Ability"){}

	bool notInScreen(Projectile* projectile){
		bool notInXBounds = (projectile->getScreenX() < 0 || projectile->getScreenX() > screenWidth);
		bool notInYBounds = (projectile->getScreenY() < 0 || projectile->getScreenY() > screenHeight);
		return notInXBounds || notInYBounds;
	}

	void performAction(SDL_Renderer* renderer, int playerX, int playerY, int mouseX, int mouseY){

		mouseX -= screenWidth / 2;
		mouseY -= screenHeight / 2;

		double direction = std::atan2(mouseY, mouseX) * TO_DEGREES;

		int playerCoords[] = { playerX, playerY };

		std::string name = "fireball " + std::to_string(projectiles.size());
		std::string filePath = "fireball.png";

		Projectile* newProjectile = new Projectile(playerCoords, 300, direction, renderer, playerX, playerY, screenWidth, screenHeight, filePath, name);

		std::map<std::string, Projectile*>::iterator it = projectiles.begin();
		projectiles.insert(it, std::pair<std::string, Projectile*>(name, newProjectile));
	}

	void updateProjectiles(float time, int playerX, int playerY) {
		std::map<std::string, Projectile*>::iterator it;
		for (it = projectiles.begin(); it != projectiles.end(); it++){
			it->second->update(time, playerX, playerY);
		}
		it = projectiles.begin();
		while (it != projectiles.end()){
			if (notInScreen(it->second)){
				projectiles.erase(it);
				it = projectiles.begin();
				continue;
			}
			it++;
		}
	}

	void renderProjectiles(SDL_Renderer* renderer){
		std::map<std::string, Projectile*>::iterator it;
		for (it = projectiles.begin(); it != projectiles.end(); it++){
			it->second->render(renderer);
		}
	}

	void update(float time, int playerX, int playerY){
		updateProjectiles(time, playerX, playerY);
	}

	void render(SDL_Renderer* renderer, int someKey){
		renderProjectiles(renderer);
	}

	~FireBall(){
		std::map<std::string, Projectile*>::iterator it;
		for (it = projectiles.begin(); it != projectiles.end(); it++){
			delete it->second;
		}
	}


private:
	std::map<std::string, Projectile*> projectiles;
};

#endif