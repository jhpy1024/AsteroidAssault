#include "Text.hpp"

Text::Text(const std::string& string, const glm::vec2& position, const glm::vec4& color, bool wordWrapEnabled)
	: m_String(string)
	, m_Position(position)
	, m_Color(color)
	, m_WordWrapEnabled(wordWrapEnabled)
{

}

void Text::setString(const std::string& string)
{
	m_String = string;
}

std::size_t Text::getStringLength() const
{
	return m_String.length();
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