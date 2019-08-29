#pragma once

#include "..\\engine\system.h"

#include "..\\core\core.h"

#include <list>
#include <map>
#include <functional>

template <typename TEvent>
class EventDispatcher : public System {
public:
	struct listener_t {
		Handle handle;
		std::function<bool(const TEvent&)> fp;

		bool operator ==(const listener_t& other) const {
			return handle == other.handle;
		}
	};

	using listeners_t = std::list<listener_t>;

public:
	EventDispatcher(Engine* engine) : System(engine) {}

	Handle Subscribe(const Name& name, std::function<bool(const TEvent&)> listener) {
		listener_t listener_s;
		listener_s.fp = listener;
		listener_s.handle = handle_id_count_;
		handle_id_count_++;

		subscribers_[name].push_back(listener_s);

		return listener_s.handle;
	}

	void Unsubscribe(const Name& name, Handle& handle) {
		auto iter = subscribers_.find(name);
		if (iter != subscribers_.end()) {
			listeners_t listeners = iter->second;
			for (auto listener : listeners) {
				if (listener.handle == handle) {
					iter->second.remove(listener);
					break;
				}
			}
		}
	}

	void Notify(const TEvent& event) {
		auto iter = subscribers_.find(event.name);
		if (iter != subscribers_.end()) {
			listeners_t listeners = iter->second;
			for (auto listener : listeners) {
				listener.fp(event);
			}
		}
	}

protected:
	std::map<Name, listeners_t> subscribers_;

	static Handle handle_id_count_;
};

template <typename TEvent>
Handle EventDispatcher<TEvent>::handle_id_count_ = 0;