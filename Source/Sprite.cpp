#include "Sprite.hpp"

Sprite::Sprite(const std::string& textureFile)
	: m_Texture(textureFile)
{

}

void Sprite::move(const glm::vec2& offset)
{
	m_Transform.move(offset);
}

void Sprite::setPosition(const glm::vec2& position)
{
	m_Transform.setPosition(position);
}

void Sprite::rotateRads(float rotation)
{
	m_Transform.rotateRads(rotation);
}

void Sprite::rotateDegs(float rotation)
{
	m_Transform.rotateDegs(rotation);
}

void Sprite::setRotationRads(float rotation)
{
	m_Transform.setRotationRads(rotation);
}

void Sprite::setRotationDegs(float rotation)
{
	m_Transform.setRotationDegs(rotation);
}

void Sprite::scale(const glm::vec2& scale)
{
	m_Transform.scale(scale);
}

void Sprite::setScale(const glm::vec2& scale)
{
	m_Transform.setScale(scale);
}

glm::mat4 Sprite::getModelMatrix() const
{
	return m_Transform.getModelMatrix();
}