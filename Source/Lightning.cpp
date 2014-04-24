#include "Lightning.hpp"
#include "Random.hpp"

#include <iostream>

Lightning::Lightning(const glm::vec2& position)
	: m_Position(position)
	, m_LastTimeAddedPoint(0)
	, POINT_CREATION_DELAY(100)
	, MAX_POINT_CREATION_DELAY_OFFSET(10)
	, MIN_MIDPOINT_OFFSET(-100.f)
	, MAX_MIDPOINT_OFFSET(100.f)
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

	glm::vec2 m0 = { (m_Position.x + m_TargetPosition.x) / 2.f, (m_Position.y + m_TargetPosition.y) / 2.f };
	glm::vec2 m1 = { (m_Position.x + m0.x) / 2.f, (m_Position.y + m0.y) / 2.f };
	glm::vec2 m2 = { (m0.x + m_TargetPosition.x) / 2.f, (m0.y + m_TargetPosition.y) / 2.f };

	m_Midpoints.push_back(m1 + getOffset());
	m_Midpoints.push_back(m0 + getOffset());
	m_Midpoints.push_back(m2 + getOffset());
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
