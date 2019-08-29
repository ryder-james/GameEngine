#pragma once

class Engine;

class System {
public:
	System(Engine* engine) : engine_(engine) {}
	virtual ~System() {}

	virtual bool Startup() { return true; }
	virtual void Update() {}
	virtual void Shutdown() {}

	Engine* GetEngine() { return engine_; }
private:
	Engine* engine_;
};
