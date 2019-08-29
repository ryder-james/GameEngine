#pragma once

template<typename T>
class Singleton {
public:
	static T* Instance() {
		if (!instance_) {
			instance_ = new T;
		}

		return instance_;
	}

	static void Destroy() {
		if (instance_) {
			delete instance_;
		}
	}

protected:
	Singleton() {}

private:
	static T* instance_;
};

template<typename T> T* Singleton<T>::instance_ = nullptr;