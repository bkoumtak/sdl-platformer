#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component {

public:
	ProjectileComponent(int rge, int sp, Vector2D vel) : range(rge), speed(sp), velocity(vel) {
	}
	~ProjectileComponent() {
	}
	
	void init() override{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
		//std::cout << "Made" << transform->position.x  << transform->position.y << std::endl;
	}
	void update() override{

		distance += speed;

		if (distance > range) {
			//std::cout << "Out of range" << std::endl;
			entity->destroy();
		}
		//out of right side of screen, etc.
		else if (transform->position.x > Game::camera.x + Game::camera.w ||
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h ||
			transform->position.y < Game::camera.y)
		{
			//std::cout << "Out of bounds" << Game::camera.w << Game::camera.h << std::endl;
			entity->destroy();
		}
	}
	
private:
	TransformComponent *transform;
	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;
};