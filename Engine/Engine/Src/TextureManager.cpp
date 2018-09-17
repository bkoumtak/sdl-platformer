#pragma once
#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* textureFile) {
	SDL_Surface *tmpSurface = IMG_Load(textureFile);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}

//For Map, getting a copy of a renderer
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {

	//ex = extra features
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL,NULL, flip);
}