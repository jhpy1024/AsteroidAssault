#include "Lightning.hpp"
#include "Random.hpp"

#include <iostream>

Lightning::Lightning(const glm::vec2& position)
	: m_Position(position)
	, m_LastTimeAddedPoint(0)
	, POINT_CREATION_DELAY(40)
	, MAX_POINT_CREATION_DELAY_OFFSET(10)
	, MIN_MIDPOINT_OFFSET(-50.f)
	, MAX_MIDPOINT_OFFSET(50.f)
{
}

void Lightning::setTargetPosition(const glm::vec2& position)
{
	m_TargetPosition = position;
}

void Lightning::update(Uint32 delta)
{
	if (pointDelayOver())
	{
		createMidpoint();
		m_LastTimeAddedPoint = SDL_GetTicks();
	}
}

void Lightning::createMidpoint()
{
	m_Midpoints.clear();

	auto getOffset = [&](){ return glm::vec2(Random::genFloat(MIN_MIDPOINT_OFFSET, MAX_MIDPOINT_OFFSET),
		0.f); };

	// Midpoint(source, target)
	glm::vec2 m0 = { (m_Position.x + m_TargetPosition.x) / 2.f, (m_Position.y + m_TargetPosition.y) / 2.f };

	// Midpoint(source, m0)
	glm::vec2 m1 = { (m_Position.x + m0.x) / 2.f, (m_Position.y + m0.y) / 2.f };

	// Midpoint(m0, target)
	glm::vec2 m2 = { (m0.x + m_TargetPosition.x) / 2.f, (m0.y + m_TargetPosition.y) / 2.f };

	// Midpoint(source, m1)
	glm::vec2 m3 = {(m_Position.x + m1.x) / 2.f, (m_Position.y + m1.y) / 2.f};

	// Midpoint(m1, m0)
	glm::vec2 m4 = { (m1.x + m0.x) / 2.f, (m1.y + m0.y) / 2.f };

	// Midpoint(m0, m2)
	glm::vec2 m5 = { (m0.x + m2.x) / 2.f, (m0.y + m2.y) / 2.f };

	// Midpoint(m2, t)
	glm::vec2 m6 = { (m2.x + m_TargetPosition.x) / 2.f, (m2.y + m_TargetPosition.y) / 2.f };

	m_Midpoints.push_back(m3 + getOffset());
	m_Midpoints.push_back(m1 + getOffset());
	m_Midpoints.push_back(m4 + getOffset());
	m_Midpoints.push_back(m0 + getOffset());
	m_Midpoints.push_back(m5 + getOffset());
	m_Midpoints.push_back(m2 + getOffset());
	m_Midpoints.push_back(m6 + getOffset());
}

bool Lightning::pointDelayOver() const
{
	auto elapsedTime = SDL_GetTicks() - m_LastTimeAddedPoint;
	auto randomDelayOffset = Random::genInt(0, MAX_POINT_CREATION_DELAY_OFFSET);

	return elapsedTime >= POINT_CREATION_DELAY + randomDelayOffset;
}

std::vector<glm::vec2>& Lightning::getMidpoints()
{
	return m_Midpoints;
}

glm::vec2 Lightning::getPosition() const
{
	return m_Position;
}

glm::vec2 Lightning::getTargetPosition() const
{
	return m_TargetPosition;
}
