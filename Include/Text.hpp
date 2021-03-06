#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>

#include <glm/glm.hpp>

class Text
{
public:
	Text(const std::string& string = "",
		 const glm::vec2& position = glm::vec2(0.f),
		 const glm::vec4& color = glm::vec4(1.f),
		 const glm::vec2& characterSize = glm::vec2(DEFAULT_WIDTH, DEFAULT_HEIGHT),
		 bool charWrapEnabled = false,
		 int wrapLimit = 0);

	void setString(const std::string& string);
	std::string getString() const;
	std::size_t getStringLength() const;

	bool isCharWrapEnabled() const;
	int getCharWrapLimit() const;
	void enableCharWrap();
	void disableCharWrap();
	void setCharWrapLimit(int limit);

	void setPosition(const glm::vec2& position);
	glm::vec2 getPosition() const;

	void setColor(const glm::vec4& color);
	glm::vec4 getColor() const;

	void setCharacterSize(const glm::vec2& size);
	glm::vec2 getCharacterSize() const;

	void rotateRads(float rotation);
	void rotateDegs(float rotation);
	void setRotationRads(float rotation);
	void setRotationDegs(float rotation);
	float getRotationRads() const;
	float getRotationDegs() const;

	void setVerticalPadding(float padding);
	void setHorizontalPadding(float padding);
	void setPadding(const glm::vec2& padding);
	float getVerticalPadding() const;
	float getHorizontalPadding() const;

public:
	static const int DEFAULT_WIDTH;
	static const int DEFAULT_HEIGHT;

private:
	std::string m_String;

	glm::vec2 m_Position;
	glm::vec2 m_CharacterSize;
	glm::vec4 m_Color;

	float m_Rotation;

	bool m_CharWrapEnabled;
	int m_WrapLimit;

	float m_VerticalPadding;
	float m_HorizontalPadding;
};

#endif