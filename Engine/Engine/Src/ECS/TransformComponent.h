#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include "../Game.h"

class TransformComponent : public Component {

public:
	Vector2D position;
	Vector2D velocity;
	
	int height = 32;
	int width = 32;
	int scale = 1;
  
	bool gravity = false; 
	bool inWater = false; 
	bool onWaterSurface = false; 
	bool onLadder = false; 
	bool onOneWay = false; 

	TransformComponent() {
		position.Zero();
		velocity.Zero(); 
	}

	TransformComponent(int sc) {
		//position.Zero();
		//middle of screen
		position.x = 400;
		position.y = 320; 
		scale = sc;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc, bool grav) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
		gravity = grav; 
	}

	void update() override {
		if (gravity)
			velocity.y += 1.5f; 
		if (inWater)
			velocity.y = 1.5f; 
		/*
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		//stop from dropping off the bottom of screen
		if (position.y >= Game::camera.y + Game::camera.h - 150 ) {
			position.y = (float)Game::camera.y + Game::camera.h - 150;
		}*/
	}

	void updateX() {
		position.x += velocity.x;
	}

	void updateY() {
		position.y += velocity.y; 
	}
};