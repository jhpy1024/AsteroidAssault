#include "ParticleSystem.hpp"
#include "TextureManager.hpp"

ParticleSystem::ParticleSystem(const std::string& textureId)
	: m_Texture(TextureManager::getInstance().getTexture(textureId))
{

}

void ParticleSystem::update(Uint32 delta)
{
	updateParticles(delta);
}

void ParticleSystem::updateParticles(Uint32 delta)
{
	for (auto& particle : m_Particles)
		particle.update(delta);
}