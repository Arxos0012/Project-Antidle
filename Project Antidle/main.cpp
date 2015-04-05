#include <iostream>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

#include "keyboard.h"
#include "World.h"
#include "player.h"
#include "ability.h"
#include "Enemy.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int mouseX, mouseY;

Keyboard gKeyboard;

bool init();		//initalizes all SDL stuff
bool loadMedia();	//loads all assets
void close();		//frees up all memory at the end

void addAbilitiesToWorld(World &world, Player &player);

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
		Player player(0, 0, 50, 50, world.getWidth(), world.getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT);
		Enemy enemy(100, -100, 50, 50, SCREEN_WIDTH, SCREEN_HEIGHT, player);

		Ability ability(-100, -100, 10, 10, SCREEN_WIDTH, SCREEN_HEIGHT, player.getX(), player.getY(), "Test Ability");

		world.addAbility(ability);

		SDL_Event e;
		
		Uint32 lastTime = SDL_GetTicks();	//returns time passed since initialization of SDL
		Uint32 currentTime;
		float timePassed, cumulativeTime = 0;

		int frames = 0;

		while (!quit){
			while (SDL_PollEvent(&e) != 0){
				if (e.type == SDL_QUIT){
					quit = true;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN || SDL_MOUSEBUTTONUP || SDL_MOUSEMOTION){
					SDL_GetMouseState(&mouseX, &mouseY);

					bool inScreen = true;
					if (mouseX < 0 || mouseX > SCREEN_WIDTH) inScreen = false;
					if (mouseY < 0 || mouseY > SCREEN_HEIGHT) inScreen = false;
				}
			}

			currentTime = SDL_GetTicks();
			timePassed = (currentTime - lastTime) / 1000.0f;	//division for conversion from milliseconds to seconds
			cumulativeTime += timePassed;
			lastTime = currentTime;

			gKeyboard.update();

			if (gKeyboard.getKeyState(SDL_SCANCODE_W)) player.moveUp(timePassed);
			if (gKeyboard.getKeyState(SDL_SCANCODE_S)) player.moveDown(timePassed);
			if (gKeyboard.getKeyState(SDL_SCANCODE_A)) player.moveLeft(timePassed);
			if (gKeyboard.getKeyState(SDL_SCANCODE_D)) player.moveRight(timePassed);
				
			world.update(player);

			enemy.move(player, timePassed);
			enemy.update(player);

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer);
			
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, world.getMapRect());

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
			SDL_RenderFillRect(gRenderer, player.getScreenRect());

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
			std::map<std::string, Ability>::iterator it;
			for (it = world.getAbilities()->begin(); it != world.getAbilities()->end(); it++){
				SDL_RenderFillRect(gRenderer, it->second.getScreenRect());
			}

			SDL_RenderPresent(gRenderer);

			if (cumulativeTime > 1){
				std::string title = "Project Antidle | fps " + std::to_string(frames / cumulativeTime);
				const char* finalTitle = title.c_str();

				SDL_SetWindowTitle(gWindow, finalTitle);
				cumulativeTime--;
				frames = 0;
			}
			frames++;
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