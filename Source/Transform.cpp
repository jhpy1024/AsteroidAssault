#include "Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
	: m_TranslationMatrix(1.f)
	, m_RotationMatrix(1.f)
	, m_ScaleMatrix(1.f)
{

}

glm::vec2 Transform::getPosition() const
{
	glm::vec2 position;

	position.x = m_TranslationMatrix[3][0];
	position.y = m_TranslationMatrix[3][1];

	return position;
}

glm::mat4 Transform::getModelMatrix() const
{
	return m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
}

glm::mat4 Transform::getTranslationMatrix() const
{
	return m_TranslationMatrix;
}

glm::mat4 Transform::getRotationMatrix() const
{
	return m_RotationMatrix;
}

glm::mat4 Transform::getScaleMatrix() const
{
	return m_ScaleMatrix;
}

void Transform::move(const glm::vec2& offset)
{
	m_TranslationMatrix = glm::translate(m_TranslationMatrix, glm::vec3(offset, 0.f));
}

void Transform::setPosition(const glm::vec2& position)
{
	m_TranslationMatrix = glm::translate(glm::mat4(1.f), glm::vec3(position, 0.f));
}

void Transform::rotateRads(float rotation)
{
	rotateDegs(glm::degrees(rotation));
}

void Transform::setRotationRads(float rotation)
{
	setRotationDegs(glm::degrees(rotation));
}

void Transform::rotateDegs(float rotation)
{
	m_RotationMatrix = glm::rotate(m_RotationMatrix, rotation, glm::vec3(0.f, 0.f, 1.f));
}

void Transform::setRotationDegs(float rotation)
{
	m_RotationMatrix = glm::rotate(glm::mat4(1.f), rotation, glm::vec3(0.f, 0.f, 1.f));
}

void Transform::scale(const glm::vec2& scale)
{
	m_ScaleMatrix = glm::scale(m_ScaleMatrix, glm::vec3(scale, 1.f));
}

void Transform::setScale(const glm::vec2& scale)
{
	m_ScaleMatrix = glm::scale(glm::mat4(1.f), glm::vec3(scale, 1.f));
}