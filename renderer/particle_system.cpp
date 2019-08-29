#include "particle_system.h"
#include "..\\core\assert.h"
#include "..\\engine\engine.h"
#include "..\\renderer\renderer.h"
#include "..\\renderer\texture.h"

ParticleSystem::ParticleSystem(Engine* engine) : System(engine) {
	particle_pool_ = new PoolAllocator<Particle>(1000);
}

ParticleSystem::~ParticleSystem() {
	delete particle_pool_;
}

void ParticleSystem::Update() {
	for (Particle* particle : particles_) {
		particle->lifetimer -= g_timer.dt;
		particle->active = (particle->lifetimer > 0.0f);

		if (particle->active) {
			particle->position = particle->position + (particle->velocity * g_timer.dt);
			particle->velocity = particle->velocity * std::pow(particle->damping, g_timer.dt);

			float t = particle->lifetimer / particle->lifetime;
			particle->scale = t;
		}
	}

	auto iter = particles_.begin();
	while (iter != particles_.end()) {
		if ((*iter)->active == false) {
			particle_pool_->Free(*iter);
			iter = particles_.erase(iter);
		} else {
			iter++;
		}
	}
}

void ParticleSystem::Draw() {
	for (Particle* particle : particles_) {
		Texture* texture = GetEngine()->GetResourceManager()->Get<Texture>(particle->texture_name);
		texture->Draw(particle->position, 0.0f, vector2::one * particle->scale, vector2(0.5f, 0.5f));
	}
}

void ParticleSystem::Create(const Name& texture_name, const vector2& position, const vector2& velocity, float damping, float lifetime) {
	Particle* particle = particle_pool_->Get();
	if (particle) {
		particle->texture_name = texture_name;
		particle->active = true;
		particle->lifetime = lifetime;
		particle->lifetimer = lifetime;

		particle->position = position;
		particle->velocity = velocity;
		particle->damping = damping;

		particles_.push_back(particle);
	}
}

