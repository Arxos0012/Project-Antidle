#include "texture.h"

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