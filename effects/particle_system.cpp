#include "particle_system.h"

ParticleSystem::ParticleSystem(size_t size) {
	pool_ = new PoolAllocator<Particle>(size);
}

ParticleSystem::~ParticleSystem() {
	delete pool_;
}

void ParticleSystem::Update(float dt) {
	for (Particle* particle : particles_) {
		particle->lifetime -= dt;
		particle->active = (particle->lifetime > 0);

		if (particle->active) {
			particle->prev_position = particle->position;
			particle->position = particle->position + (particle->velocity * dt);
			particle->velocity *= particle->damping;
		}
	}
	auto iter = particles_.begin();
	while (iter != particles_.end()) {
		if (!(*iter)->active) {
			pool_->Free(*iter);
			iter = particles_.erase(iter);
		} else {
			iter++;
		}
	}
}

void ParticleSystem::Draw(Core::Graphics& graphics) {
	for (Particle* particle : particles_) {
		graphics.SetColor(particle->color);
		graphics.DrawLine(particle->position.x, particle->position.y, particle->prev_position.x, particle->prev_position.y);
	}
}

void ParticleSystem::Create(const vector2& position, const vector2& velocity, const color& color, float damping, float lifetime) {
	Particle* particle = pool_->Get();
	if (particle) {
		particle->active = true;
		particle->position = position;
		particle->prev_position = position;
		particle->velocity = velocity;
		particle->color = color;
		particle->damping = damping;
		particle->lifetime = lifetime;

		particles_.push_back(particle);
	}
}
