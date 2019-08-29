#pragma once

#include "particle.h"
#include "..\\engine\system.h"
#include "..\\core\pool_allocator.h"

class ParticleSystem : public System {
public:
	ParticleSystem(Engine* engine);
	~ParticleSystem();

	void Update() override;
	void Draw();

	void Create(const Name& texture_name, const vector2& position, const vector2& velocity, float damping, float lifetime);

protected:
	PoolAllocator<Particle>* particle_pool_;
	std::list<Particle*> particles_;
};
