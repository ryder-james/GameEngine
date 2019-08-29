#pragma once

#include "..\\core\core.h"

#include <functional>
#include <map>

struct State {
	std::function<void()> Enter;
	std::function<void()> Update;
	std::function<void()> Exit;
};

template <typename T>
class StateMachine {
public:
	StateMachine(T* owner) : owner_(owner) {}
	~StateMachine() {}

	void Update();
	void AddState(const Name& name, const State& state);
	void SetState(const Name& name);

private:
	T* owner_ = nullptr;

	State* state_ = nullptr;
	std::map<Name, State> states_;
};

template<typename T>
inline void StateMachine<T>::Update() {
	if (state_) {
		if (state_->Update) state_->Update();
	}
}

template<typename T>
inline void StateMachine<T>::AddState(const Name& name, const State& state) {
	ASSERT(states_.find(name) == states_.end());
	states_[name] = state;
}

template<typename T>
inline void StateMachine<T>::SetState(const Name& name) {
	if (states_.find(name) != states_.end()) {
		State* new_state = &states_[name];
		if (new_state != state_) {
			if (state_ && state_->Exit) state_->Exit();
			state_ = new_state;
			if (state_->Enter) state_->Enter();
			if (state_->Update) state_->Update();
		}
	}
}
