#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

//ID is size_t
using ComponentID = std::size_t;
using Group = std::size_t;

//func put into place wherever used
inline ComponentID getNewComponentTypeID() {
	//static so counts
	//u = unsigned
	static ComponentID lastID = 0u;
	return lastID++;
}

//so the same type has the same ID each time
template <typename T>
inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
//layers
constexpr std::size_t maxGroups = 32;

//See if object has this component
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
//See how many/which components the object has
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public: 
	Entity *entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	
	virtual ~Component() {}
};

//has all entities in the class
class Entity {

private:
	Manager &manager;
	bool active = true;
	//dynamic size array
	std::vector < std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:
	//everytime we create an entity we pass in a manager
	Entity(Manager &mManager) : manager(mManager) {}
	void update() {	 
		//for all components, update
		for (auto& c : components) c->update();
	}
	void draw() {
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }

	void destroy() { active = false; }

	bool hasGroup(Group mGroup) {
		return groupBitSet[mGroup];
	}

	void addGroup(Group mGroup);

	void delGroup(Group mGroup) {
		groupBitSet[mGroup] = false;
	}

	template <typename T> 
	bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> 
	T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
		//example as can used
		//gameObject.getComponent<PositionComponent>().setXPos(25);
	}
};

class Manager {

private:
	std::vector<std::unique_ptr<Entity>> entities;
	//maxGroups = size, has entity pointers
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	void update() {
		for (auto& e : entities) e->update();
	}
	void draw() {
		for (auto& e : entities) e->draw();
	}
	//remove entities at each frame as needed
	void refresh() {
		//move through each group
		for (auto i(0u); i < maxGroups; i++) {
			//v vector
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity) 
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
			[](const std::unique_ptr<Entity> &mEntity) 
		//the remove_if function
		{
			return !mEntity->isActive();
		}),
		std::end(entities));

	}

	void AddToGroup(Entity* mEntity, Group mGroup) {
		//put the group in the back of the given entity vector
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup) {
		//gives the list of entities inside the group
		return groupedEntities[mGroup];
	}

	Entity& addEntity() {
		//this = manager 
		Entity* e = new Entity(*this);
		//initialize the ptr to e
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};