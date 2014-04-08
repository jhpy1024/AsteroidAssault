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
		 bool wordWrapEnabled = false);

	void setString(const std::string& string);
	std::size_t getStringLength() const;

	void enableWordWrap();
	void disableWordWrap();
	void setWordWrapLimit(int limit);

	void setPosition(const glm::vec2& position);
	glm::vec2 getPosition() const;

	void setColor(const glm::vec4& color);
	glm::vec4 getColor() const;

private:
	std::string m_String;

	glm::vec2 m_Position;
	glm::vec4 m_Color;

	bool m_WordWrapEnabled;
	int m_WrapLimit;
};

#endif