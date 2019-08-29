#pragma once

#include <string>
#include <map>

template<typename TBase>
class CreatorBase {
public:
	virtual ~CreatorBase() {}
	virtual TBase* Create() const = 0;
};

template<typename TBase, typename TKey = std::string>
class Factory {
public:
	~Factory();

	template<typename T = TBase>
	T* Create(TKey key);
	void Register(TKey key, CreatorBase<TBase>* creator);

private:
	using registry_t = std::map<TKey, CreatorBase<TBase>*>;
	registry_t registry_;
};

template<typename T, typename TBase>
class Creator : public CreatorBase<TBase> {
public:
	virtual TBase* Create() const { return new T; }
};

template<typename TBase>
class Spawner : public CreatorBase<TBase> {
public:
	Spawner(TBase* instance) : instance_(instance) {}
	virtual ~Spawner() {
		instance_->Destroy();
		delete instance_;
	}

	virtual TBase* Create() const {
		return instance_->Clone();
	}

private:
	TBase* instance_ = nullptr;
};

template<typename TBase, typename TKey>
inline Factory<TBase, TKey>::~Factory() {
	for (const auto& iter : registry_) {
		delete iter.second;
	}

	registry_.clear();
}

template<typename TBase, typename TKey>
template<typename T>
inline T* Factory<TBase, TKey>::Create(TKey key) {
	auto iter = registry_.find(key);
	if (iter == registry_.end()) { return nullptr; }

	CreatorBase<TBase>* creator = (*iter).second;

	return dynamic_cast<T*>(creator->Create());
}

template<typename TBase, typename TKey>
inline void Factory<TBase, TKey>::Register(TKey key, CreatorBase<TBase>* creator) {
	if (registry_.find(key) == registry_.end()) {
		registry_[key] = creator;
	}
}
