#ifndef FIREBALL_H
#define FIREBALL_H

#include <map>
#include "ability.h"
#include "projectile.h"

class FireBall : public Ability{
public:
	FireBall(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, int playerX, int playerY)
		: Ability(renderer,x,y,screenWidth,screenHeight,playerX,playerY,"test_ability.png","Fireball Ability"){}

	void performAction(SDL_Renderer* renderer, int playerX, int playerY, int mouseX, int mouseY){

		mouseX -= screenWidth / 2;
		mouseY -= screenHeight / 2;

		if (freeProjectiles.size() == 0){
			double direction = std::atan2(mouseY, mouseX) * TO_DEGREES;

			int playerCoords[] = { playerX, playerY };

			std::string name = "fireball " + std::to_string(usedProjectiles.size());
			std::string filePath = "fireball.png";

			Projectile* newProjectile = new Projectile(playerCoords, 300, direction, renderer, playerX, playerY, screenWidth, screenHeight, filePath, name);

			std::map<std::string, Projectile*>::iterator it = usedProjectiles.begin();
			usedProjectiles.insert(it, std::pair<std::string, Projectile*>(name, newProjectile));
		}
		else{
			std::map<std::string, Projectile*>::iterator ft = freeProjectiles.begin();
			std::map<std::string, Projectile*>::iterator it = usedProjectiles.begin();

			usedProjectiles.insert(it, std::pair<std::string, Projectile*>(ft->first, ft->second));
			freeProjectiles.erase(ft);
		}
	}

	void updateProjectiles(float time, int playerX, int playerY) {
		std::map<std::string, Projectile*>::iterator it;
		for (it = usedProjectiles.begin(); it != usedProjectiles.end(); it++){
			it->second->update(time, playerX, playerY);
		}
		it = usedProjectiles.begin();
		std::map<std::string, Projectile*>::iterator ft;
		while (it != usedProjectiles.end()){
			if (abs(it->second->getScreenX()) > screenWidth / 2 || abs(it->second->getScreenY()) > screenHeight / 2){
				it->second->setX(playerX);
				it->second->setY(playerY);

				ft = freeProjectiles.begin();
				freeProjectiles.insert(ft, std::pair<std::string, Projectile*>(it->first, it->second));
				usedProjectiles.erase(it);
				it = usedProjectiles.begin();
				continue;
			}
			it++;
		}

	}

	void renderProjectiles(SDL_Renderer* renderer){
		std::map<std::string, Projectile*>::iterator it;
		for (it = usedProjectiles.begin(); it != usedProjectiles.end(); it++){
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
		for (it = usedProjectiles.begin(); it != usedProjectiles.end(); it++){
			delete it->second;
		}
		for (it = freeProjectiles.begin(); it != freeProjectiles.end(); it++){
			delete it->second;
		}
	}


private:
	std::map<std::string, Projectile*> usedProjectiles;
	std::map<std::string, Projectile*> freeProjectiles;
};

#endif