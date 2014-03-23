#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>

class Transform
{
public:
	Transform();

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
	glm::vec2 getScale() const;
	
private:
	glm::mat4 m_TranslationMatrix;
	glm::mat4 m_RotationMatrix;
	glm::mat4 m_ScaleMatrix;
};

#endif