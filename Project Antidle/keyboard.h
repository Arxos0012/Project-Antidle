#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL.h>

class Keyboard{
public:
	static void update(){
		keyboard = SDL_GetKeyboardState(NULL);
	}

	static bool getKeyState(int scanKeyCode){
		return keyboard[scanKeyCode];
	}

private:
	static const Uint8* keyboard;
};

#endif