#include "ParticleSystem.hpp"
#include "TextureManager.hpp"

#include <algorithm>

ParticleSystem::ParticleSystem(const std::string& textureId)
	: m_Texture(TextureManager::getInstance().getTexture(textureId))
{

}

void ParticleSystem::move(const glm::vec2& offset)
{
	m_Position += offset;
}

void ParticleSystem::setPosition(const glm::vec2& position)
{
	m_Position = position;
}

void ParticleSystem::update(Uint32 delta)
{
	updateParticles(delta);
	removeDeadParticles();
}

void ParticleSystem::updateParticles(Uint32 delta)
{
	for (auto& particle : m_Particles)
		particle.update(delta);
}

void ParticleSystem::removeDeadParticles()
{
	m_Particles.erase(std::remove_if(m_Particles.begin(), m_Particles.end(), [](Particle& p){ return p.isAlive(); }), m_Particles.end());
}