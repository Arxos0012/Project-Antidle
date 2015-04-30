#include "player.h"

void Player::setX(int x){
	if (abs(x) > (worldWidth - screenRect.w) / 2){
		if (center.x > 0) center.x = (worldWidth - screenRect.w) / 2;
		else center.x = (-worldWidth + screenRect.w) / 2;
	}
	else center.x = x;
}

void Player::setY(int y){
	if (abs(y) > (worldHeight - screenRect.h) / 2){
		if (center.y > 0) center.y = (worldHeight - screenRect.h) / 2;
		else center.y = (-worldHeight + screenRect.h) / 2;
	}
	else center.y = y;
}

void Player::moveLeft(float time){
	x -= MOVESPEED*time;
	if (x < (-worldWidth + screenRect.w) / 2) x = (-worldWidth + screenRect.w) / 2;
	center.x = (int)x;
}

void Player::moveRight(float time){
	x += MOVESPEED*time;
	if (x >(worldWidth - screenRect.w) / 2) x = (worldWidth - screenRect.w) / 2;
	center.x = (int)x;
}

void Player::moveUp(float time){
	y -= MOVESPEED*time;
	if (y < (-worldHeight + screenRect.h) / 2) y = (-worldHeight + screenRect.h) / 2;
	center.y = (int)y;
}

void Player::moveDown(float time){
	y += MOVESPEED*time;
	if (y >(worldHeight - screenRect.h) / 2) y = (worldHeight - screenRect.h) / 2;
	center.y = (int)y;
}

void Player::addAbility(Ability* ability){
	std::map<std::string, Ability*>::iterator it = abilities.begin();
	abilities.insert(it, std::pair<std::string, Ability*>(ability->getName(), ability));
	abilities.at(ability->getName())->markAsPlayerOwned();

	if (abilities.size() < 3){
		if (primeAbilities[0] == NULL) primeAbilities[0] = ability;
		else primeAbilities[1] = ability;
	}
}

void Player::removeAbiltiy(std::string &name){
	std::map<std::string, Ability*>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->first == name){
			abilities.erase(it);
			return;
		}
	}
}

Ability* Player::getAbility(std::string &name){
	std::map<std::string, Ability*>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->first == name) return it->second;
	}
	return NULL;
}

void Player::update(SDL_Renderer* renderer, float time, std::vector<Static*>& stats){
	controls.update();

	if (controls.getKeyState(SDL_SCANCODE_W)) moveUp(time);
	if (controls.getKeyState(SDL_SCANCODE_S)) moveDown(time);
	if (controls.getKeyState(SDL_SCANCODE_A)) moveLeft(time);
	if (controls.getKeyState(SDL_SCANCODE_D)) moveRight(time);

	std::vector<Static*>::iterator st;
	for (st = stats.begin(); st != stats.end(); st++){
		untouch(*st, time);
	}

	std::map<std::string, Ability*>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (controls.getLeftMouseButton() && it->second->getName() == "Fireball Ability")
			it->second->performAction(renderer, center.x, center.y, controls.getMouseX(), controls.getMouseY());
	}
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->second->getName() == "Fireball Ability") it->second->update(time, center.x, center.y);
	}

}

void Player::untouch(Static* stat, float time){
	int staticA[] = { stat->getX() - stat->getWidth() / 2, stat->getY() - stat->getHeight() / 2 };
	int staticB[] = { stat->getX() + stat->getWidth() / 2, stat->getY() + stat->getHeight() / 2 };

	int playerA[] = { center.x - screenRect.w / 2, center.y - screenRect.h / 2 };
	int playerB[] = { center.x + screenRect.w / 2, center.y + screenRect.h / 2 };
	
	//checking player top and bottom edges
	if ((playerA[0] >= staticA[0] && playerA[0] <= staticB[0]) || (playerB[0] >= staticA[0] && playerB[0] <= staticB[0])){
		//top edge
		if (playerA[1] <= staticB[1] && playerB[1] > staticB[1]){
			moveDown(time);
		}

		//bottom edge
		if (playerB[1] >= staticA[1] && playerA[1] < staticA[1]){
			moveUp(time);
		}
	}

	//checking player left and right edges
	if ((playerA[1] >= staticA[1] && playerA[1] <= staticB[1]) || (playerB[1] >= staticA[1] && playerB[1] <= staticB[1])){
		//left edge
		if (playerA[0] <= staticB[0] && playerB[0] > staticB[0]){
			moveRight(time);
		}

		//right edge
		if (playerB[0] >= staticA[0] && playerA[0] < staticA[0]){
			moveLeft(time);
		}
	}
}

void Player::render(SDL_Renderer* renderer){
	SDL_Point center = { screenWidth / 2, screenHeight / 2 };
	texture.render(screenRect.x, screenRect.y, renderer, NULL, 0, &center);

	std::map<std::string, Ability*>::iterator it;
	for (it = abilities.begin(); it != abilities.end(); it++){
		if (it->second->getName() == "Fireball Ability") it->second->render(renderer, 0);
	}

	//rendering icons for the prime abilities
	for (int i = 0; i < 2; i++){
		if (primeAbilities[i] != NULL){
			primeAbilities[i]->renderIcon(renderer, ICON_SPACING*(i + 1) + primeAbilities[i]->getIconWidth()*i, ICON_SPACING);
		}
	}
}