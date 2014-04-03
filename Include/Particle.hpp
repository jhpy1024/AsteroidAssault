#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/glm.hpp>

#include <SDL.h>

struct Particle
{
	Particle(const glm::vec2& position, const glm::vec2& velocity, Uint32 lifetime,	const glm::vec4& color = glm::vec4(1.f, 1.f, 1.f, 1.f));

	void update(Uint32 delta);

	bool isAlive() const;

	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec4 color;

private:
	Uint32 m_Lifetime;
	Uint32 m_TimeCreated;
};

#endif