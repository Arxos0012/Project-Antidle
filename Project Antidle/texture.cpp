#include "texture.h"
#include <iostream>

Texture::Texture(){
	texture = NULL;
	width = height = 0;
}

Texture::~Texture(){
	free();
}

void Texture::free(){
	if (texture != NULL){
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = height = 0;
	}
}

void Texture::setColorMod(Uint8 r, Uint8 g, Uint8 b){
	SDL_SetTextureColorMod(texture, r, g, b);
}

void Texture::setAlphaMod(Uint8 a){
	SDL_SetTextureAlphaMod(texture, a);
}

void Texture::setBlending(SDL_BlendMode blending){
	SDL_SetTextureBlendMode(texture, blending);
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
	SDL_Rect renderQuad = { x, y, width, height };
	if (clip != NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

bool Texture::loadTexture(std::string path, SDL_Renderer* renderer){
	free();
	
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x79, 0x77, 0x77));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL){
			printf("Unable to create texture from surface %s! SDL Error %s\n", path.c_str(), SDL_GetError());
		}
		else{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	this->path = path;
	texture = newTexture;
	return texture != NULL;
}