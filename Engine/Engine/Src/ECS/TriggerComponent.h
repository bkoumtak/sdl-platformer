#pragma once
#include <string>
#include "SDL.h"
#include "ECS.h"
#include "TransformComponent.h"

class TriggerComponent : public Component {

public: 
	SDL_Rect collider; 
	std::string tag; 

	TriggerComponent(std::string t) : tag(t) {}; 
	TriggerComponent(std::string t, int xPos, int yPos, int size) : tag(t)
	{
		collider.x = xPos; 
		collider.y = yPos; 
		collider.h = collider.w = size; 
	}
	
	void onTrigger(TransformComponent& tComp) {
		if (tag == "water") {
			tComp.gravity = -0.3f; 
		}
	}
};