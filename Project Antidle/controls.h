#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL.h>

class Controls{
public:
	void setEvent(SDL_Event *e){
		this->event = e;
	}

	void update(){
		keyboard = SDL_GetKeyboardState(NULL);
	}

	Uint8 getKeyState(int scanKeyCode){
		return keyboard[scanKeyCode];
	}

	bool getLeftMouseButton(){
		return (event->type == SDL_MOUSEBUTTONDOWN && (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)));
	}

	bool getRightMouseButton(){
		return (event->type == SDL_MOUSEBUTTONDOWN && (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT)));
	}

	int getMouseX(){ return mouseX; }
	int getMouseY(){ return mouseY; }

private:
	int mouseX, mouseY;
	const Uint8* keyboard;
	SDL_Event* event;
};

#endif