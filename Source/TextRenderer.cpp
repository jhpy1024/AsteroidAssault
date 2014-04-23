#include "TextRenderer.hpp"
#include "ShaderManager.hpp"

#include <iostream>

void TextRenderer::init()
{
	m_VertexBuffer.init();
	m_ColorBuffer.init();
	m_TexCoordBuffer.init();
}

void TextRenderer::render(Text& text, Texture& texture)
{
	std::vector<Text> texts;
	texts.push_back(text);

	render(texts, texture);
}

void TextRenderer::render(std::vector<Text>& texts, Texture& texture)
{;
	if (texts.empty()) return;

	auto textureSize = glm::vec2(texture.width, texture.height);

	clearVectors();

	for (auto& text : texts)
	{
		float xOffset = 0.f;
		float yOffset = 0.f;

		for (int i = 0; i < text.getStringLength(); ++i)
		{
			auto character = text.getString()[i];
			auto charIndex = character - 33;
			auto charSize = text.getCharacterSize();

			int numCharsHorizontal = textureSize.x / Text::DEFAULT_WIDTH;
			int numCharsVertical = textureSize.y / Text::DEFAULT_HEIGHT;
			auto texBoundX = (charIndex % numCharsHorizontal) * Text::DEFAULT_WIDTH;
			auto texBoundY = (charIndex / numCharsVertical) * Text::DEFAULT_HEIGHT;

			if (text.isCharWrapEnabled() && (i % text.getCharWrapLimit() == 0))
			{
				xOffset = -(charSize.x * i) - (text.getHorizontalPadding() * i);
				yOffset -= (charSize.y + text.getVerticalPadding());
			}
			
			TextureBounds texBounds;
			texBounds.bottomLeft = { texBoundX, texBoundY };
			texBounds.size = { Text::DEFAULT_WIDTH, Text::DEFAULT_HEIGHT };

			addVertices({ text.getPosition().x + (charSize.x * i) + (text.getHorizontalPadding() * i) + xOffset, text.getPosition().y + yOffset }, charSize, text.getRotationRads());
			addTexCoords(texBounds, textureSize);
			addColors(text);
		}

	}

	texture.bind();

	passDataToBuffers();

	auto particleShader = ShaderManager::getInstance().getShader("Particle");

	m_VertexBuffer.bind();
	particleShader->bind();
	particleShader->setupVertexAttribPointer("in_Position");

	m_TexCoordBuffer.bind();
	particleShader->setupVertexAttribPointer("in_TexCoords");
	particleShader->setUniform("in_Texture", texture.getId());

	m_ColorBuffer.bind();
	particleShader->setupVertexAttribPointer("in_Color", 4);

	particleShader->setUniform("in_CameraShakeEnabled", 0);
	glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.getNumVertices());
	particleShader->setUniform("in_CameraShakeEnabled", 1);
}

void TextRenderer::clearVectors()
{
	m_Vertices.clear();
	m_TexCoords.clear();
	m_Colors.clear();
}

void TextRenderer::addVertices(const glm::vec2& position, const glm::vec2& size, float rotationRads)
{
	auto sinAngle = glm::sin(rotationRads);
	auto cosAngle = glm::cos(rotationRads);

	auto offsetFromCenter = glm::vec2(-size.x / 2.f, -size.y / 2.f);
	auto bottomLeft = glm::vec2(position.x + (offsetFromCenter.x * cosAngle - offsetFromCenter.y * sinAngle),
		position.y - (-offsetFromCenter.y * cosAngle - offsetFromCenter.x * sinAngle));

	offsetFromCenter = glm::vec2(size.x / 2.f, -size.y / 2.f);
	auto bottomRight = glm::vec2(position.x + (offsetFromCenter.x * cosAngle - offsetFromCenter.y * sinAngle),
		position.y - (-offsetFromCenter.y * cosAngle - offsetFromCenter.x * sinAngle));

	offsetFromCenter = glm::vec2(size.x / 2.f, size.y / 2.f);
	auto topRight = glm::vec2(position.x + (offsetFromCenter.x * cosAngle - offsetFromCenter.y * sinAngle),
		position.y - (-offsetFromCenter.y * cosAngle - offsetFromCenter.x * sinAngle));

	offsetFromCenter = glm::vec2(-size.x / 2.f, size.y / 2.f);
	auto topLeft = glm::vec2(position.x + (offsetFromCenter.x * cosAngle - offsetFromCenter.y * sinAngle),
		position.y - (-offsetFromCenter.y * cosAngle - offsetFromCenter.x * sinAngle));

	// Bottom Left
	m_Vertices.push_back(bottomLeft.x);
	m_Vertices.push_back(bottomLeft.y);

	// Bottom Right
	m_Vertices.push_back(bottomRight.x);
	m_Vertices.push_back(bottomRight.y);

	// Top Right
	m_Vertices.push_back(topRight.x);
	m_Vertices.push_back(topRight.y);

	// Top Right (2)
	m_Vertices.push_back(topRight.x);
	m_Vertices.push_back(topRight.y);

	// Top Left
	m_Vertices.push_back(topLeft.x);
	m_Vertices.push_back(topLeft.y);

	// Bottom Left (2)
	m_Vertices.push_back(bottomLeft.x);
	m_Vertices.push_back(bottomLeft.y);
}

void TextRenderer::addTexCoords(const TextureBounds& textureBounds, const glm::vec2& textureSize)
{
	// Bottom Left
	m_TexCoords.push_back(textureBounds.bottomLeft.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.bottomLeft.y) / textureSize.y);

	// Bottom Right
	m_TexCoords.push_back((textureBounds.bottomLeft.x + textureBounds.size.x) / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.bottomLeft.y) / textureSize.y);

	// Top Right
	m_TexCoords.push_back((textureBounds.bottomLeft.x + textureBounds.size.x) / textureSize.x);
	m_TexCoords.push_back((textureSize.y - (textureBounds.bottomLeft.y + textureBounds.size.y)) / textureSize.y);

	// Top Right (2)
	m_TexCoords.push_back((textureBounds.bottomLeft.x + textureBounds.size.x) / textureSize.x);
	m_TexCoords.push_back((textureSize.y - (textureBounds.bottomLeft.y + textureBounds.size.y)) / textureSize.y);

	// Top Left
	m_TexCoords.push_back(textureBounds.bottomLeft.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - (textureBounds.bottomLeft.y + textureBounds.size.y)) / textureSize.y);

	// Bottom Left (2)
	m_TexCoords.push_back(textureBounds.bottomLeft.x / textureSize.x);
	m_TexCoords.push_back((textureSize.y - textureBounds.bottomLeft.y) / textureSize.y);
}

void TextRenderer::addColors(const Text& text)
{
	for (int i = 0; i < 6; ++i)
	{
		auto color = text.getColor();
		m_Colors.push_back(color.x);
		m_Colors.push_back(color.y);
		m_Colors.push_back(color.z);
		m_Colors.push_back(color.w);
	}
}

void TextRenderer::passDataToBuffers()
{
	m_VertexBuffer.setVertices(m_Vertices);
	m_TexCoordBuffer.setVertices(m_TexCoords);
	m_ColorBuffer.setColor(m_Colors);
}