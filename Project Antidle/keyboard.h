#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL.h>

class Keyboard{
public:
	void update(){
		keyboard = SDL_GetKeyboardState(NULL);
	}

	Uint8 getKeyState(int scanKeyCode){
		return keyboard[scanKeyCode];
	}

private:
	const Uint8* keyboard;
};

#endif