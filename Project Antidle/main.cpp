#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <SDL_timer.h>
#include <map>
#include "keyboard.h"
#include "World.h"
#include "Enemy.h"
#include "ability.h"
#include "player.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int mouseX, mouseY;

int MOVE_SPEED;	//movement speed of the player in pixels per second

Keyboard gKeyboard;
Player testPlayer;

float player[] = { 0, 0 };

int playerColor[] = { 0x00, 0xFF, 0x00 };

SDL_Rect gPlayer;

std::map<int, Ability> abilites;
std::map<int, Ability> playerAbilites;

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

		World world(550, 550);

		MOVE_SPEED = world.getWidth() / 2;

		gPlayer.x = SCREEN_WIDTH/2 - 25;
		gPlayer.y = SCREEN_HEIGHT/ 2 - 25;
		gPlayer.w = 50;
		gPlayer.h = 50;

		Enemy testDummy(-200, -200);

		Ability testAbility(200, 200);

		std::cout << abilites.size() << "\n";

		abilites[Ability::TEST_ABILITY] = testAbility;

		std::cout << abilites.size() << "\n";

		SDL_Event e;
		
		Uint32 lastTime = SDL_GetTicks();	//returns time passed since initialization of SDL
		Uint32 currentTime;
		float timePassed;

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

					if (inScreen){
						int color[3];
						std::map<int, Ability>::iterator it = playerAbilites.find(Ability::TEST_ABILITY);
						if (e.type == SDL_MOUSEBUTTONDOWN && (playerAbilites.find(Ability::TEST_ABILITY) != playerAbilites.end())){
							color[0] = 0xAA;
							color[1] = 0xAA;
							color[2] = 0xAA;
						}
						if (e.type == SDL_MOUSEBUTTONUP){
							color[0] = 0x00;
							color[1] = 0xFF;
							color[2] = 0x00;
						}
						testPlayer.setPlayerColor(color);
					}
				}
			}

			currentTime = SDL_GetTicks();
			timePassed = (currentTime - lastTime) / 1000.0f;	//division for conversion from milliseconds to seconds
			lastTime = currentTime;

			gKeyboard.update();

			if (gKeyboard.getKeyState(SDL_SCANCODE_W)){
				testPlayer.setY(testPlayer.getY() - (testPlayer.getMoveSpeed() * timePassed));
				if (testPlayer.getY() - testPlayer.getHeight() / 2 < -world.getHeight() / 2) testPlayer.setY((-world.getHeight() + testPlayer.getHeight()) / 2.0f);
			}
			if (gKeyboard.getKeyState(SDL_SCANCODE_S)){
				testPlayer.setY(testPlayer.getY() + (testPlayer.getMoveSpeed() * timePassed));
				if (testPlayer.getY() + testPlayer.getHeight() / 2 > world.getHeight() / 2) testPlayer.setY((world.getHeight() - testPlayer.getHeight()) / 2.0f);
			}
			if (gKeyboard.getKeyState(SDL_SCANCODE_A)){
				testPlayer.setX(testPlayer.getX() - (testPlayer.getMoveSpeed() * timePassed));
				if (testPlayer.getX() - testPlayer.getWidth() / 2 < -world.getWidth() / 2) testPlayer.setX((-world.getWidth() + testPlayer.getWidth()) / 2.0f);
			}
			if (gKeyboard.getKeyState(SDL_SCANCODE_D)){
				testPlayer.setX(testPlayer.getX() + (testPlayer.getMoveSpeed() * timePassed));
				if (testPlayer.getX() + testPlayer.getWidth() / 2 > world.getWidth() / 2) testPlayer.setX((world.getWidth() - testPlayer.getWidth()) / 2.0f);
			}

			world.setX((int)((SCREEN_WIDTH - world.getWidth()) / 2 - testPlayer.getX()));
			world.setY((int)((SCREEN_HEIGHT - world.getHeight()) / 2 - testPlayer.getY()));

			std::map<int, Ability>::iterator jt;
			if (abilites.size() > 0){
				for (jt = abilites.begin(); jt != abilites.end(); jt++){
					float distance = sqrt(pow(player[0] - jt->second.getX(), 2) + pow(player[1] - jt->second.getY(), 2));
					if (distance <= 25 && abilites.size() > 0){
						playerAbilites[jt->first] = jt->second;
						abilites.erase(jt->first);
						if (abilites.size() == 0) break;
					}
				}
			}

			testDummy.move(player, timePassed);
			int dummyCoords[2];
			testDummy.getCoords(dummyCoords);
			world.coordWorldToScreen(dummyCoords, player, testDummy.getWidth(), testDummy.getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT);
			testDummy.refeshScreenCoords(dummyCoords);

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer);

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, world.getMapRect());
			
			SDL_SetRenderDrawColor(gRenderer, playerColor[0], playerColor[1], playerColor[2], 0xFF);
			SDL_RenderFillRect(gRenderer, &gPlayer);
			
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderFillRect(gRenderer, testDummy.getScreenRect());

			if (abilites.size() > 0){
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
				std::map<int, Ability>::iterator it;
				for (it = abilites.begin(); it != abilites.end(); it++){
					int testCoords[2];
					it->second.getCoords(testCoords);
					world.coordWorldToScreen(testCoords, player, it->second.getWidth(), it->second.getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT);
					it->second.refreshScreenCoords(testCoords);
					SDL_RenderFillRect(gRenderer, it->second.getScreenRect());
				}
			}

			SDL_RenderPresent(gRenderer);

			std::string title = "Project Antidle | fps " + std::to_string((int)(1 / timePassed));
			const char* finalTitle = title.c_str();

			SDL_SetWindowTitle(gWindow, finalTitle);
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