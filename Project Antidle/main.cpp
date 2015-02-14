#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <SDL_timer.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int MAP_WIDTH = 3000;
const int MAP_HEIGHT = 3000;

const Uint8* gKeyboard = NULL;

const int MOVE_SPEED = 1500;	//movement speed of the player in pixels per second

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

		gPlayer.x = SCREEN_WIDTH/2 - 50;
		gPlayer.y = SCREEN_HEIGHT/ 2 - 50;
		gPlayer.w = 100;
		gPlayer.h = 100;

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

			gKeyboard = SDL_GetKeyboardState(NULL);
			
			if (gKeyboard[SDL_SCANCODE_W]) playerY -= MOVE_SPEED * timePassed;
			if (gKeyboard[SDL_SCANCODE_S]) playerY += MOVE_SPEED * timePassed;
			if (gKeyboard[SDL_SCANCODE_A]) playerX -= MOVE_SPEED * timePassed;
			if (gKeyboard[SDL_SCANCODE_D]) playerX += MOVE_SPEED * timePassed;

			gMap.x = (int)((SCREEN_WIDTH - MAP_WIDTH)/2 - playerX);
			gMap.y = (int)((SCREEN_HEIGHT - MAP_HEIGHT) / 2 - playerY);

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer);

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, &gMap);
			
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderFillRect(gRenderer, &gPlayer);

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