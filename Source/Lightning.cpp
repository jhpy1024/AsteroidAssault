#include "Lightning.hpp"
#include "Random.hpp"

Lightning::Lightning(const glm::vec2& position)
	: m_Position(m_Position)
	, m_LastTimeAddedPoint(0)
	, POINT_CREATION_DELAY(200)
	, MAX_POINT_CREATION_DELAY_OFFSET(300)
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
	glm::vec2 midpoint = { (m_Position.x + m_TargetPosition.x) / 2.f, (m_Position.y + m_TargetPosition.y) / 2.f };
	glm::vec2 offset = { Random::genFloat(MIN_MIDPOINT_OFFSET, MAX_MIDPOINT_OFFSET),
						 Random::genFloat(MIN_MIDPOINT_OFFSET, MAX_MIDPOINT_OFFSET) };

	m_Midpoints.push_back(midpoint + offset);
}

bool Lightning::pointDelayOver() const
{
	auto elapsedTime = SDL_GetTicks() - m_LastTimeAddedPoint;
	auto randomDelayOffset = Random::genInt(0, MAX_POINT_CREATION_DELAY_OFFSET);

	return elapsedTime >= POINT_CREATION_DELAY + randomDelayOffset;
}

glm::vec2 Lightning::getPosition() const
{
	return m_Position;
}

glm::vec2 Lightning::getTargetPosition() const
{
	return m_TargetPosition;
}