#include "Sprite.hpp"

Sprite::Sprite(const std::string& textureFile)
	: m_Texture(textureFile)
	, m_Size(m_Texture.width, m_Texture.height)
{

}

void Sprite::move(const glm::vec2& offset)
{
	m_Position += offset;
	m_Transform.move(offset);
}

void Sprite::setPosition(const glm::vec2& position)
{
	m_Position = position;
	m_Transform.setPosition(position);
}

void Sprite::rotateRads(float rotation)
{
	m_Rotation += glm::degrees(rotation);
	m_Transform.rotateRads(rotation);
}

void Sprite::rotateDegs(float rotation)
{
	m_Rotation += rotation;
	m_Transform.rotateDegs(rotation);
}

void Sprite::setRotationRads(float rotation)
{
	m_Rotation = glm::degrees(rotation);
	m_Transform.setRotationRads(rotation);
}

void Sprite::setRotationDegs(float rotation)
{
	m_Rotation = rotation;
	m_Transform.setRotationDegs(rotation);
}

void Sprite::scale(const glm::vec2& scale)
{
	m_Size *= scale;
	m_Transform.scale(scale);
}

void Sprite::setScale(const glm::vec2& scale)
{
	auto originalSize = glm::vec2(m_Texture.width, m_Texture.height);
	m_Size = originalSize * scale;
	m_Transform.setScale(scale);
}

glm::vec2 Sprite::getSize() const
{
	return m_Size;
}

float Sprite::getRotationDegs() const
{
	return m_Rotation;
}

float Sprite::getRotationRads() const
{
	return glm::radians(m_Rotation);
}

glm::vec2 Sprite::getPosition() const
{
	return m_Position;
}

glm::mat4 Sprite::getModelMatrix() const
{
	return m_Transform.getModelMatrix();
}

glm::mat4 Sprite::getTranslationMatrix() const
{
	return m_Transform.getTranslationMatrix();
}

glm::mat4 Sprite::getRotationMatrix() const
{
	return m_Transform.getRotationMatrix();
}

glm::mat4 Sprite::getScaleMatrix() const
{
	return m_Transform.getScaleMatrix();
}