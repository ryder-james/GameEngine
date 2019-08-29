#pragma once

#include "object.h"
#include "..\\framework\factory.h"

#include <list>

class Engine;
class Entity;
class Object;

class ObjectFactory : public Factory<Object, Name> {};

class Scene : public Object {
public:
	Scene() {}

	bool Create(const Name& name, Engine* engine);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Scene* Clone() override { return new Scene(*this); }

	void Initialize() override;

	void Update();
	void Draw();

	void Add(Entity* entity);
	std::list<Entity*>::iterator Remove(Entity* entity, bool destroy = true);

	Entity* GetEntityWithName(const Name& name);
	std::vector<Entity*> GetEntitiesWithTag(const Name& tag);

	Engine* GetEngine() { return engine_; }
	ObjectFactory* GetObjectFactory() { return object_factory_; }

private:
	bool LoadEntities(const rapidjson::Value& value);

protected:
	Engine* engine_ = nullptr;
	ObjectFactory* object_factory_ = nullptr;

	std::list<Entity*> entities_;
};