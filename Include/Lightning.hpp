#ifndef LIGHTNING_HPP
#define LIGHTNING_HPP

#include <SDL.h>
#include <vector>
#include <glm/glm.hpp>

class Lightning
{
public:
	Lightning(const glm::vec2& position);

	void setTargetPosition(const glm::vec2& position);

	void update(Uint32 delta);

	glm::vec2 getPosition() const;
	glm::vec2 getTargetPosition() const;
	std::vector<glm::vec2>& getMidpoints();

private:
	bool pointDelayOver() const;
	void createMidpoint();

private:
	glm::vec2 m_Position;
	glm::vec2 m_TargetPosition;

	std::vector<glm::vec2> m_Midpoints;

	Uint32 m_LastTimeAddedPoint;
	const Uint32 POINT_CREATION_DELAY;
	const Uint32 MAX_POINT_CREATION_DELAY_OFFSET;

	const float MIN_MIDPOINT_OFFSET;
	const float MAX_MIDPOINT_OFFSET;
};

#endif