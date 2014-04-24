#include "Lightning.hpp"
#include "Random.hpp"
#include "MathUtils.hpp"

#include <iostream>

Lightning::Lightning(const glm::vec2& position)
	: m_Position(position)
	, m_LastTimeAddedPoint(0)
	, POINT_CREATION_DELAY(500)
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

	auto m0 = MathUtils::midpoint(m_Position, m_TargetPosition) + getOffset();
	auto m1 = MathUtils::midpoint(m_Position, m0) + getOffset();
	auto m2 = MathUtils::midpoint(m0, m_TargetPosition) + getOffset();
	auto m3 = MathUtils::midpoint(m_Position, m1) + getOffset();
	auto m4 = MathUtils::midpoint(m1, m0) + getOffset();
	auto m5 = MathUtils::midpoint(m0, m2) + getOffset();
	auto m6 = MathUtils::midpoint(m2, m_TargetPosition) + getOffset();

	m_Midpoints.insert(m_Midpoints.end(), { m3, m1, m4, m0, m5, m2, m6 });
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
