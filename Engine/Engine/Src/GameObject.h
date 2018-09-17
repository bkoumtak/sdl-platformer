#include "Game.h"

class GameObject {

public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	//Update for its own specific behaviors
	void Update();
	void Render();

private:
	int xPos;
	int yPos;
	
	SDL_Texture *objTexture;
	SDL_Rect srcRect, destRect;

};

