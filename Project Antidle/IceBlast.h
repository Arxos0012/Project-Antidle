#ifndef ICEBLAST_H
#define ICEBLAST_H

#include "ability.h"

class IceBlast : public Ability{
public:
	IceBlast(SDL_Renderer* renderer, int x, int y, int screenWidth, int screenHeight, int playerX, int playerY, std::string iconPath)
		: Ability(renderer, x, y, screenWidth, screenHeight, playerX, playerY, iconPath, "IceBlast Ability"){}
	
	bool notInScreen(Projectile* projectile){
		bool notInXBounds = (projectile->getScreenX() < 0 || projectile->getScreenX() > screenWidth);
		bool notInYBounds = (projectile->getScreenY() < 0 || projectile->getScreenY() > screenHeight);
		return notInXBounds || notInYBounds;
	}

	void performAction(SDL_Renderer* renderer, int playerX, int playerY){
		int playerCoords[] = { playerX, playerY };
		Projectile* newSpread[8];
		for (int i = 0; i < 8; i++){
			newSpread[i] = new Projectile(playerCoords, 300, (i/8.0)*2*M_PI*TO_DEGREES, renderer, playerX, playerY, screenWidth, screenHeight, "ice shard.png", "ice shard");
		}

		std::map<std::string, Projectile*>::iterator it;
		for (int j = 0; j < 8; j++){
			it = projectiles.begin();
			projectiles.insert(it, std::pair<std::string, Projectile*>(newSpread[j]->getName(), newSpread[j]));
		}
		

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

	~IceBlast(){
		std::map<std::string, Projectile*>::iterator it;
		for (it = projectiles.begin(); it != projectiles.end(); it++){
			delete it->second;
		}
	}
};

#endif