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
#include "Enemy.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int mouseX, mouseY;

Controls gControls;

bool init();		//initalizes all SDL stuff
bool loadMedia();	//loads all assets
void close();		//frees up all memory at the end

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int main(int argc, char* argv[]){
	if (!init()){
		std::cerr << "Falied to initialize!\n";
	}
	else if (!loadMedia()){
		std::cerr << "Falied to load media!\n";
	}
	else{
		bool quit = false;

		World world(550, 550, SCREEN_WIDTH, SCREEN_HEIGHT);
		Player player(gRenderer, 0, 0, world.getWidth(), world.getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT, "player.png");
		Enemy enemy(gRenderer, 100, -100, SCREEN_WIDTH, SCREEN_HEIGHT, player, "enemy.png");

		FireBall fireball(gRenderer, -100, -100, SCREEN_WIDTH, SCREEN_HEIGHT, player.getX(), player.getY());
		fireball.setKey(SDL_SCANCODE_E);

		world.addAbility(&fireball);

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

			//getting time passed
			currentTime = SDL_GetTicks();
			timePassed = (currentTime - lastTime) / 1000.0f;	//division for conversion from milliseconds to seconds
			cumulativeTime += timePassed;
			lastTime = currentTime;

			//player input
			player.update(gRenderer, timePassed);
			
			//moving things in the world (and the world of course) based on time and player's position
			world.update(player);

			enemy.update(player, timePassed);

			//correctly managing abilities between the world and the player
			std::map<std::string, Ability*>::iterator at;
			for (at = world.getAbilities()->begin(); at != world.getAbilities()->end(); at++){
				float distance = sqrt(pow(at->second->getX() - player.getX(), 2) + pow(at->second->getY() - player.getY(), 2));
				if (distance <= 20){
					std::string name = at->first;
					Ability* transfer = world.getAbility(name);
					player.addAbility(transfer);
					world.removeAbility(name);
					if (world.getAbilities()->size() == 0) break;
				}
			}

			//clearing screen
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer);
			
			//drawing the world
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, world.getMapRect());

			player.render(gRenderer);	//rendering the player
			enemy.render(gRenderer);	//rendering the enemy

			//rendering the abilites
			std::map<std::string, Ability*>::iterator it;
			for (it = world.getAbilities()->begin(); it != world.getAbilities()->end(); it++){
				it->second->render(gRenderer);
			}

			SDL_RenderPresent(gRenderer);

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