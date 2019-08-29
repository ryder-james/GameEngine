#pragma once

#include "object.h"
#include "..\\math\transform.h"
#include "..\\core\core.h"

class Scene;
class Component;

class Entity : public Object {
public:
	enum State {
		kActive,
		kVisible,
		kDestroy,
		kTransient
	};

public:
	Entity() {}
	Entity(Scene* owner) : scene_(owner){}
	Entity(const Entity& entity);

	bool Create(const Name& name, Scene* scene);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Entity* Clone() override { return new Entity(*this); };

	void Initialize() override;

	void Update();
	void Draw();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template <typename T>
	T* GetComponent() {
		T* component = nullptr;
		for (Component* _component : components_) {
			component = dynamic_cast<T*>(_component);
			if (component != nullptr) break;
		}

		return component;
	}

	void SetTag(const Name& tag) { tag_ = tag; }
	const Name& GetTag() const { return tag_; }

	transform& GetTransform() { return transform_; }

	void SetScene(Scene* scene) { scene_ = scene; }
	Scene* GetScene() { return scene_; }

	bool IsSpawner() { return is_spawner_; }

	void AddChild(Entity* child);
	std::vector<Entity*> GetChildren() { return children_; }
	Entity* GetParent() { return parent_; }

protected:
	bool LoadComponents(const rapidjson::Value& value);

public:
	bit_mask_t state_ = BIT(kActive) | BIT(kVisible);
	transform local_transform_;

protected:
	float lifetime_ = 0.0f;

	bool is_spawner_;
	Name tag_;

	transform transform_;

	Scene* scene_ = nullptr;
	Entity* parent_ = nullptr;

	std::vector<Component*> components_;
	std::vector<Entity*> children_;
};
