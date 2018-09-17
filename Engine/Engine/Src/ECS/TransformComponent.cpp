#include "TransformComponent.h"
#include "ECS.h"

TransformComponent::TransformComponent() {
	position.Zero();
}

TransformComponent::TransformComponent(int sc) {
	//position.Zero();
	//middle of screen
	position.x = 400;
	position.y = 320;
	scale = sc;
}

TransformComponent::TransformComponent(float x, float y) {
	position.x = x;
	position.y = y;
}

TransformComponent::TransformComponent(float x, float y, int h, int w, int sc) {
	position.x = x;
	position.y = y;
	height = h;
	width = w;
	scale = sc;
}

void TransformComponent::update() {

	position.x += velocity.x * speed;
	position.y += velocity.y * speed;

	//stop from dropping off the bottom of screen
	if (position.y >= Game::camera.y + Game::camera.h - 150) {
		position.y = (float)Game::camera.y + Game::camera.h - 150;
	}
}

//like Unity's onAwake
void TransformComponent::init() {
	velocity.Zero();
}