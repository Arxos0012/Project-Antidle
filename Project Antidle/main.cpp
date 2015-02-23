#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <SDL_timer.h>
#include "keyboard.h"
#include "ability.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int MAP_WIDTH = 550;
const int MAP_HEIGHT = 550;

const int MOVE_SPEED = MAP_WIDTH / 2;	//movement speed of the player in pixels per second

Keyboard gKeyboard;

float playerX = 0;
float playerY = 0;

SDL_Rect gPlayer;

bool init();		//initalizes all SDL stuff
bool loadMedia();	//loads all assets
void close();		//frees up all memory at the end

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Rect gMap;

int main(int argc, char* argv[]){
	if (!init()){
		std::cerr << "Falied to initialize!\n";
	}
	else if (!loadMedia()){
		std::cerr << "Falied to load media!\n";
	}
	else{
		bool quit = false;

		gMap.w = MAP_WIDTH;
		gMap.h = MAP_HEIGHT;

		gPlayer.x = SCREEN_WIDTH/2 - 25;
		gPlayer.y = SCREEN_HEIGHT/ 2 - 25;
		gPlayer.w = 50;
		gPlayer.h = 50;

		int ableRadius = 10;
		Ability testAbility(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 100);

		SDL_Event e;
		
		Uint32 lastTime = SDL_GetTicks();	//returns time passed since initialization of SDL
		Uint32 currentTime;
		float timePassed;

		while (!quit){
			while (SDL_PollEvent(&e) != 0){
				if (e.type == SDL_QUIT){
					quit = true;
				}
			}

			currentTime = SDL_GetTicks();
			timePassed = (currentTime - lastTime) / 1000.0f;	//division for conversion from milliseconds to seconds
			lastTime = currentTime;

			gKeyboard.update();
			
			if (gKeyboard.getKeyState(SDL_SCANCODE_W)){
				playerY -= MOVE_SPEED * timePassed;
				if ( playerY - gPlayer.h/2 < -MAP_HEIGHT / 2) playerY = (-MAP_HEIGHT + gPlayer.h) / 2.0f;
			}
			if (gKeyboard.getKeyState(SDL_SCANCODE_S)){
				playerY += MOVE_SPEED * timePassed;
				if (playerY + gPlayer.h/2 > MAP_HEIGHT / 2) playerY = (MAP_HEIGHT - gPlayer.h) / 2.0f;
			}
			if (gKeyboard.getKeyState(SDL_SCANCODE_A)){
				playerX -= MOVE_SPEED * timePassed;
				if (playerX - gPlayer.w/2 < -MAP_WIDTH / 2) playerX = (-MAP_WIDTH + gPlayer.w) / 2.0f;
			}
			if (gKeyboard.getKeyState(SDL_SCANCODE_D)){
				playerX += MOVE_SPEED * timePassed;
				if (playerX + gPlayer.w/2 > MAP_WIDTH / 2) playerX = (MAP_WIDTH - gPlayer.w) / 2.0f;
			}

			std::cout << "(" << playerX << ", " << playerY << ")\n";

			gMap.x = (int)((SCREEN_WIDTH - MAP_WIDTH) / 2 - playerX);
			gMap.y = (int)((SCREEN_HEIGHT - MAP_HEIGHT) / 2 - playerY);
			testAbility.setX((int)(testAbility.getX() - playerX));
			testAbility.setY((int)(testAbility.getY() - playerY));

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer);

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, &gMap);
			
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderFillRect(gRenderer, &gPlayer);

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderFillRect(gRenderer, testAbility.getRect());

			SDL_RenderPresent(gRenderer);
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