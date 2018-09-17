#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y) {
	
	objTexture = TextureManager::LoadTexture(textureSheet);

	xPos = x;
	yPos = y;
}

GameObject::~GameObject() {
}

void GameObject::Update() {

	xPos++;
	yPos++;

	//Use full width and height of the png
	srcRect.h = 32;
	srcRect.w = 32;

	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

}

void GameObject::Render() {

	//Draws the texture
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}


