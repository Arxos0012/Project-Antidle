#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>

class Texture{
public:
	Texture();
	~Texture();

	void loadTexture(std::string path, SDL_Renderer* renderer);	//loads texture from a file

	void setColorMod(Uint8 r, Uint8 g, Uint8 b);	//sets color modulation
	void setAlphaMod(Uint8 a);						//sets alpha modulation
	void setBlending(SDL_BlendMode blending);		//sets alpha blending

	void free();

	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);	//renders texture to screen

	int getWidth() { return width; }	//returns width of texture
	int getHeight(){ return height; }	//returns height of texture

private:
	SDL_Texture* texture;
	int width, height;
};

#endif