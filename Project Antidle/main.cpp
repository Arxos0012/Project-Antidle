#include <iostream>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

#include "controls.h"
#include "World.h"
#include "player.h"

#include "FireBall.h"
#include "IceBlast.h"
#include "Enemy.h"
#include "static.h"
#include "texture.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Controls gControls;

bool init();		//initalizes all SDL stuff
bool loadMedia();	//loads all assets
void close();		//frees up all memory at the end

float getDistance(int x, int y, int a, int b);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool gameOver = false, victory = false, gameOverInitiated = false;

int main(int argc, char* argv[]){
	if (!init()){
		std::cerr << "Falied to initialize!\n";
	}
	else if (!loadMedia()){
		std::cerr << "Falied to load media!\n";
	}
	else{
		bool quit = false;

		std::map <std::string, Enemy*> enemies;
		std::map <std::string, Enemy*>::iterator et = enemies.begin();

		World world(3000, 3000, SCREEN_WIDTH, SCREEN_HEIGHT);
		Player player(gRenderer, 0, 0, world.getWidth(), world.getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT, "player.png");

		Enemy enemy1(gRenderer, -1100, -1400, SCREEN_WIDTH, SCREEN_HEIGHT, player, "enemy.png", "enemy1");
		Enemy enemy2(gRenderer, -1100, -1200, SCREEN_WIDTH, SCREEN_HEIGHT, player, "enemy.png", "enemy2");
		Enemy enemy3(gRenderer, 1100, 1400, SCREEN_WIDTH, SCREEN_HEIGHT, player, "enemy.png", "enemy3");
		Enemy enemy4(gRenderer, 1100, 1200, SCREEN_WIDTH, SCREEN_HEIGHT, player, "enemy.png", "enemy4");
		Enemy enemy5(gRenderer, -1400, 1400, SCREEN_WIDTH, SCREEN_HEIGHT, player, "enemy.png", "enemy5");
		Enemy enemy6(gRenderer, 1400, -1400, SCREEN_WIDTH, SCREEN_HEIGHT, player, "enemy.png", "enemy6");

		enemies.insert(et, std::pair<std::string, Enemy*>(enemy1.getName(), &enemy1));
		enemies.insert(et, std::pair<std::string, Enemy*>(enemy2.getName(), &enemy2));
		enemies.insert(et, std::pair<std::string, Enemy*>(enemy3.getName(), &enemy3));
		enemies.insert(et, std::pair<std::string, Enemy*>(enemy4.getName(), &enemy4));
		enemies.insert(et, std::pair<std::string, Enemy*>(enemy5.getName(), &enemy5));
		enemies.insert(et, std::pair<std::string, Enemy*>(enemy6.getName(), &enemy6));

		FireBall fireball(gRenderer, -1400, -1400, SCREEN_WIDTH, SCREEN_HEIGHT, player.getX(), player.getY(), "fireball icon.png");
		IceBlast iceblast(gRenderer, 1400, 1400, SCREEN_WIDTH, SCREEN_HEIGHT, player.getX(), player.getY(), "iceblast icon.png");

		Static *northWall[23], *southWall[23], *eastWall[22], *westWall[22];

		for (int i = 0; i < 23; i++){
			northWall[i] = new Static(gRenderer, -1250 + (100 * i), -1250, player.getX(), player.getY(), SCREEN_WIDTH, SCREEN_HEIGHT, "brick.png", "northwall" + std::to_string(i));
			world.addStatic(northWall[i]);
		}

		for (int i = 0; i < 23; i++){
			southWall[i] = new Static(gRenderer, 1250 - (100 * i), 1250, player.getX(), player.getY(), SCREEN_WIDTH, SCREEN_HEIGHT, "brick.png", "southwall" + std::to_string(i));
			world.addStatic(southWall[i]);
		}

		for (int i = 0; i < 22; i++){
			westWall[i] = new Static(gRenderer, -1250, -1150 + (100 * i), player.getX(), player.getY(), SCREEN_WIDTH, SCREEN_HEIGHT, "brick.png", "westwall" + std::to_string(i));
			world.addStatic(westWall[i]);
		}

		for (int i = 0; i < 22; i++){
			eastWall[i] = new Static(gRenderer, 1250, 1150 - (100 * i), player.getX(), player.getY(), SCREEN_WIDTH, SCREEN_HEIGHT, "brick.png", "eastwall" + std::to_string(i));
			world.addStatic(eastWall[i]);
		}

		world.addAbility(&fireball);
		world.addAbility(&iceblast);

		Texture gameOverTexture, victoryTexture, freezeFrame;
		gameOverTexture.loadTexture("gameover.png", gRenderer);
		victoryTexture.loadTexture("victory.png", gRenderer);

		SDL_Event e;
		gControls.setEvent(&e);
		player.setControls(gControls);
		
		Uint32 lastTime = SDL_GetTicks();	//returns time passed since initialization of SDL
		Uint32 currentTime;
		float timePassed, cumulativeTime = 0;

		int frames = 0;

		while (!quit){
			while (SDL_PollEvent(&e) != 0){
				if (e.type == SDL_QUIT){
					quit = true;
				}
			}

			if (!gameOver){

				//getting time passed
				currentTime = SDL_GetTicks();
				timePassed = (currentTime - lastTime) / 1000.0f;	//division for conversion from milliseconds to seconds
				cumulativeTime += timePassed;
				lastTime = currentTime;

				//player input
				player.update(gRenderer, timePassed, world.getOnScreenStatics());

				//moving things in the world (and the world of course) based on time and player's position
				world.update(player);

				std::map<std::string, Projectile*> playerProjectiles = player.getFiredProjectiles();
				std::map<std::string, Projectile*>::iterator pt;

				bool wasErased = false;

				et = enemies.begin();
				while (et != enemies.end()){
					et->second->update(player, timePassed);
					pt = playerProjectiles.begin();
					while (pt != playerProjectiles.end()){
						if (getDistance(et->second->getX(), et->second->getY(), pt->second->getX(), pt->second->getY()) <= 50){
							enemies.erase(et);
							wasErased = true;
							et = enemies.begin();
							break;
						}
						pt++;
					}
					if (wasErased){
						wasErased = false;
						continue;
					}
					et++;
				}

				//correctly managing abilities between the world and the player
				std::map<std::string, Ability*>::iterator at = world.getAbilities()->begin();
				while (at != world.getAbilities()->end()){
					if (getDistance(at->second->getX(), at->second->getY(), player.getX(), player.getY()) <= 50){
						std::string name = at->first;
						Ability* transfer = world.getAbility(name);
						player.addAbility(transfer);
						world.removeAbility(name);
						at = world.getAbilities()->begin();
						continue;
					}
					at++;
				}

				//clearing screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);

				//drawing the world
				SDL_SetRenderDrawColor(gRenderer, 0x4C, 0x69, 0x4B, 0xFF);
				SDL_RenderFillRect(gRenderer, world.getMapRect());

				player.render(gRenderer);	//rendering the player

				for (et = enemies.begin(); et != enemies.end(); ++et){
					et->second->render(gRenderer);
				}

				//rendering the abilites
				world.render(gRenderer);

				//shows final product on screen
				SDL_RenderPresent(gRenderer);

				if (enemies.size() == 0) gameOver = victory = gameOverInitiated = true;

				for (et = enemies.begin(); et != enemies.end(); et++){
					if (getDistance(player.getX(), player.getY(), et->second->getX(), et->second->getY()) <= 50){
						gameOver = gameOverInitiated = true;
					}
				}

				frames++;
				//Displays current FPS of game in the title every second
				if (cumulativeTime >= 1){
					std::string title = "Project Antidle | fps " + std::to_string(frames / cumulativeTime);
					const char* finalTitle = title.c_str();

					SDL_SetWindowTitle(gWindow, finalTitle);
					cumulativeTime--;
					frames = 0;
				}
			}
			else{
				if (gameOverInitiated){
					if (victory) victoryTexture.render((SCREEN_WIDTH - gameOverTexture.getWidth()) / 2, (SCREEN_HEIGHT - gameOverTexture.getHeight()) / 2, gRenderer);
					else gameOverTexture.render((SCREEN_WIDTH - gameOverTexture.getWidth()) / 2, (SCREEN_HEIGHT - gameOverTexture.getHeight()) / 2, gRenderer);
					
					SDL_Surface *sshot = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
					SDL_RenderReadPixels(gRenderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
					SDL_SaveBMP(sshot, "freezeframe.bmp");
					SDL_FreeSurface(sshot);
					freezeFrame.loadTexture("freezeframe.bmp", gRenderer);
					gameOverInitiated = false;
				}
				//clearing screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);

				freezeFrame.render(0, 0, gRenderer);

				//shows freeze frame on screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	return 0;
}

bool init(){
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Failed to initialze SDL! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		gWindow = SDL_CreateWindow("Project Antidle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL){
			printf("Failed to create game window! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL){
				printf("Failed to create game renderer! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else{
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)){
					printf("SDL_image failed to initialize: SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

float getDistance(int x, int y, int a, int b){
	return sqrt(pow(x - a, 2) + pow(y - b, 2));
}

bool loadMedia(){
	bool success = true;

	return success;
}

void close(){

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	
	IMG_Quit();
	SDL_Quit();
}