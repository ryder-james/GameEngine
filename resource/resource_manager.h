#pragma once

#include "..\\framework\manager.h"

template <typename TBase, size_t N = 65536>
class ResourceManager : public Manager<TBase, N> {
public:
	ResourceManager(Renderer* renderer) : renderer_(renderer) {}
	~ResourceManager();

	template <typename T = TBase>
	T* Get(const Name& name);

	void Add(const Name& name, TBase* resource);
	void Remove(const Name& name) override;
	void RemoveAll() override;

private:
	Renderer* renderer_;
};

template<typename TBase, size_t N>
inline ResourceManager<TBase, N>::~ResourceManager() {
	RemoveAll();
}

template<typename TBase, size_t N>
template<typename T>
T* ResourceManager<TBase, N>::Get(const Name& name) {
	u32 index = name.GetID() % N;
	T* element = dynamic_cast<T*>(Manager<TBase, N>::elements_[index]);

	if (element == nullptr) {
		element = new T(renderer_);
		element->Create(name);
		Manager<TBase, N>::elements_[index] = element;
	}

	return element;
}

template<typename TBase, size_t N>
inline void ResourceManager<TBase, N>::Add(const Name& name, TBase* resource) {
	u32 index = name.GetID() % N;
	TBase* element = Manager<TBase, N>::elements_[index];
	ASSERT(element == nullptr);

	Manager<TBase, N>::elements_[index] = resource;
}

template<typename TBase, size_t N>
void ResourceManager<TBase, N>::Remove(const Name& name) {
	u32 index = name.GetID() % N;
	TBase* element = Manager<TBase, N>::elements_[index];
	if (element) {
		element->Destroy();
		delete element;
		Manager<TBase, N>::elements_[index] = nullptr;
	}
}

template<typename TBase, size_t N>
void ResourceManager<TBase, N>::RemoveAll() {
	for (size_t i = 0; i < N; i++) {
		TBase* element = Manager<TBase, N>::elements_[i];
		if (element) {
			element->Destroy();
			delete element;
			Manager<TBase, N>::elements_[i] = nullptr;
		}
	}
}
