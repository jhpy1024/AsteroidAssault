#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>

#include "Transform.hpp"
#include "Texture.hpp"
#include "TextureBounds.hpp"

class Sprite
{
public:
	Sprite();

	void move(const glm::vec2& offset);
	void setPosition(const glm::vec2& position);

	void rotateRads(float rotation);
	void rotateDegs(float rotation);
	void setRotationRads(float rotation);
	void setRotationDegs(float rotation);

	void scale(const glm::vec2& scale);
	void setScale(const glm::vec2& scale);

	glm::mat4 getTranslationMatrix() const;
	glm::mat4 getRotationMatrix() const;
	glm::mat4 getScaleMatrix() const;
	glm::mat4 getModelMatrix() const;
	glm::vec2 getPosition() const;
	glm::vec2 getSize() const;
	float getRotationDegs() const;
	float getRotationRads() const;

	void setTextureBounds(const TextureBounds& textureBounds);
	void setTextureBounds(const glm::vec2& bottomLeft, const glm::vec2& size);
	TextureBounds getTextureBounds() const;

	void bindTexture();

public:
	static const int SPRITESHEET_WIDTH;
	static const int SPRITESHEET_HEIGHT;

private:
	TextureBounds getDefaultTextureBounds() const;
	glm::vec2 getDefaultSize() const;

private:
	TextureBounds m_TextureBounds;

	Transform m_Transform;

	glm::vec2 m_Position;
	glm::vec2 m_Size;
	float m_Rotation;
};

#endif