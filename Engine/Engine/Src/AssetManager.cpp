#include "AssetManager.h"
#include "ECS\TransformComponent.h"
#include "ECS\SpriteComponent.h"
#include "ECS\ProjectileComponent.h"
#include "ECS\ColliderComponent.h"

AssetManager::AssetManager(Manager* man): manager(man) {
}
AssetManager::~AssetManager() {
}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id){
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1, false);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range,speed, vel);
	projectile.addComponent<ColliderComponent>(TT_PROJECTILE);
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path) {
	//emplace for map, need an id and a SDL_Texture* 
	textures.emplace(id, TextureManager::LoadTexture(path));
}
SDL_Texture* AssetManager::GetTexture(std::string id) {
	return textures[id];
}