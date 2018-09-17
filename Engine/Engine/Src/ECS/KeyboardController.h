#pragma once

#include "ECS.h"
#include "../Game.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <iostream>

class Gravity;
class SpriteComponent;

class KeyboardController : public Component {

public:
	TransformComponent *transform;
	SpriteComponent *sprite;
	//Gravity *grav;

	//keep transform as it is for the entity at the current time
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		//grav = &entity->getComponent<Gravity>();
	}

	void update() override {
		bool ignoreJump = false; 

		if (!transform->inWater)
			sprite->Play("Idle"); 

		if (Game::keyStateArray[SDLK_s] == KEY_PRESSED && Game::keyStateArray[SDLK_SPACE] == KEY_PRESSED)
		{
			//std::cout << "ho"; 
			if (transform->onOneWay) {
				transform->position.y += 1;
				ignoreJump = true; 
			}
		}

		if (Game::event.type == SDL_KEYDOWN ) {
			//virtual code for the key
			switch (Game::event.key.keysym.sym) {

				
			case SDLK_a:
				transform->velocity.x = -3;
				if (transform->inWater)
					sprite->Play("Swim"); 
				else 
					sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 3;
				if (transform->inWater)
					sprite->Play("Swim"); 
				else 
					sprite->Play("Walk");

				sprite->spriteFlip = SDL_FLIP_NONE;
				
				break;
			case SDLK_w:
				if (transform->onLadder) {
					transform->gravity = false; 
					transform->inWater = false; 
					transform->velocity.y = -3; 
				}
				if (!transform->gravity)
					transform->velocity.y = -3;
				break;
			case SDLK_s:
				if (!transform->gravity)
					transform->velocity.y = 3;

				//if (transform->onOneWay)
					//transform->position.y += 1;
				break; 
			case SDLK_SPACE:   
				if (!ignoreJump) {
					if (transform->gravity)
						transform->velocity.y = -20.0f;

					if (transform->inWater && transform->onWaterSurface) {
						transform->velocity.y = -60.0f;
					}
					else if (transform->inWater)
						transform->velocity.y = -40.0f;
				}
				break; 

			default: 
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			//reset back to 0 once done pressing

			case SDLK_a:
				if (transform->velocity.x < 0) {
					transform->velocity.x = 0;
				}
				//sprite->Play("Idle");
				//resets horizontal flipping so walking isn't moonwalking
				//sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				if (transform->velocity.x > 0) {
					transform->velocity.x = 0;
				}
				//sprite->Play("Idle");
				break;
			case SDLK_w:
				if (transform->velocity.y < 0 && !transform->gravity)
					transform->velocity.y = 0;
				break;
			case SDLK_s: 
				if (transform->velocity.y > 0 && !transform->gravity)
					transform->velocity.y = 0;
				break; 

			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
		} 

	}
};
