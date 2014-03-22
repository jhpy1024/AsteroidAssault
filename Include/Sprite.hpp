#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>

#include "Transform.hpp"
#include "Texture.hpp"

class Sprite
{
public:
	Sprite(const std::string& textureFile);

	void move(const glm::vec2& offset);
	void setPosition(const glm::vec2& position);

	void rotateRads(float rotation);
	void rotateDegs(float rotation);
	void setRotationRads(float rotation);
	void setRotationDegs(float rotation);

	void scale(const glm::vec2& scale);
	void setScale(const glm::vec2& scale);

	glm::mat4 getModelMatrix() const;

private:
	Texture m_Texture;
	Transform m_Transform;
};

#endif