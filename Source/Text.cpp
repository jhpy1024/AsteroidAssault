#include "Text.hpp"

const int Text::DEFAULT_WIDTH = 10;
const int Text::DEFAULT_HEIGHT = 10;

Text::Text(const std::string& string, const glm::vec2& position, const glm::vec4& color, const glm::vec2& characterSize, bool wordWrapEnabled)
	: m_String(string)
	, m_Position(position)
	, m_Color(color)
	, m_Rotation(0.f)
	, m_WordWrapEnabled(wordWrapEnabled)
	, m_CharacterSize(characterSize)
	, m_WrapLimit(0)
{

}

void Text::setString(const std::string& string)
{
	m_String = string;
}

std::string Text::getString() const
{
	return m_String;
}

std::size_t Text::getStringLength() const
{
	return m_String.length();
}

bool Text::isWordWrapEnabled() const
{
	return m_WordWrapEnabled;
}

int Text::getWordWrapLimit() const
{
	return m_WrapLimit;
}

void Text::enableWordWrap()
{
	m_WordWrapEnabled = true;
}

void Text::disableWordWrap()
{
	m_WordWrapEnabled = false;
}

void Text::setWordWrapLimit(int limit)
{
	m_WrapLimit = limit;
}

void Text::setPosition(const glm::vec2& position)
{
	m_Position = position;
}

glm::vec2 Text::getPosition() const
{
	return m_Position;
}

void Text::setColor(const glm::vec4& color)
{
	m_Color = color;
}

glm::vec4 Text::getColor() const
{
	return m_Color;
}

void Text::setCharacterSize(const glm::vec2& size)
{
	m_CharacterSize = size;
}

glm::vec2 Text::getCharacterSize() const
{
	return m_CharacterSize;
}

void Text::rotateRads(float rotation)
{
	m_Rotation += glm::degrees(rotation);
}

void Text::rotateDegs(float rotation)
{
	m_Rotation += rotation;
}

void Text::setRotationRads(float rotation)
{
	m_Rotation = glm::degrees(rotation);
}

void Text::setRotationDegs(float rotation)
{
	m_Rotation = rotation;
}

float Text::getRotationRads() const
{
	return glm::radians(m_Rotation);
}

float Text::getRotationDegs() const
{
	return m_Rotation;
}