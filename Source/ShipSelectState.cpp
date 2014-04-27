#include "ShipSelectState.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Mouse.hpp"
#include "StateManager.hpp"
#include "PlayState.hpp"

#include <memory>

void ShipSelectState::init()
{
	m_CurrentShip = static_cast<PlayerShipType>(0);

	m_ShipPreview.setTextureBounds(getTextureBounds());
	m_ShipPreview.setScale({ 2.f, 2.f });
	m_ShipPreview.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT / 2.f });

	m_LeftArrow.setTextureBounds({ 0.f, 0.f }, { 98.f, 150.f });
	m_LeftArrow.setScale({ 0.75f, 0.75f });
	m_LeftArrow.setPosition({ (98.f / 2.f) + 20.f, Game::HEIGHT / 2.f });

	m_RightArrow.setTextureBounds({ 98.f, 0.f }, { 98.f, 150.f });
	m_RightArrow.setScale({ 0.75f, 0.75f });
	m_RightArrow.setPosition({ Game::WIDTH - (98.f / 2.f) - 20.f, Game::HEIGHT / 2.f });

	m_SelectButton.setTextureBounds({ 0.f, 150.f }, { 300.f, 50.f });
	m_SelectButton.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT * 0.08f });

	m_Title.setTextureBounds({ 0.f, 200.f }, { 825.f, 45.f });
	m_Title.setScale({ 0.75f, 0.75f });
	m_Title.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT * 0.9f });

	m_LeftRect.position = m_LeftArrow.getPosition();
	m_LeftRect.width = m_LeftArrow.getSize().x;
	m_LeftRect.height = m_LeftArrow.getSize().y;

	m_RightRect.position = m_RightArrow.getPosition();
	m_RightRect.width = m_RightArrow.getSize().x;
	m_RightRect.height = m_RightArrow.getSize().y;

	m_SelectRect.position = m_SelectButton.getPosition();
	m_SelectRect.width = m_SelectButton.getSize().x;
	m_SelectRect.height = m_SelectButton.getSize().y;

	m_MouseRect.width = m_MouseRect.height = 2.f;

	m_Sprites.push_back(m_LeftArrow);
	m_Sprites.push_back(m_RightArrow);
	m_Sprites.push_back(m_SelectButton);
	m_Sprites.push_back(m_Title);
}

void ShipSelectState::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
			leftButtonPressed();
	}
}

void ShipSelectState::handleKeyPress(SDL_Keycode key)
{
	if (key == SDLK_LEFT || key == SDLK_a)
		previousShip();
	else if (key == SDLK_RIGHT || key == SDLK_d)
		nextShip();
}

void ShipSelectState::previousShip()
{
	auto currentIndex = static_cast<int>(m_CurrentShip);

	if (currentIndex > 0)
	{
		m_CurrentShip = static_cast<PlayerShipType>(currentIndex - 1);
		m_ShipPreview.setTextureBounds(getTextureBounds());
		m_ShipPreview.setScale({ 2.f, 2.f });
	}
}

void ShipSelectState::nextShip()
{
	auto currentIndex = static_cast<int>(m_CurrentShip);
	auto lastIndex = static_cast<int>(PlayerShipType::Last) - 1;

	if (currentIndex < lastIndex)
	{
		m_CurrentShip = static_cast<PlayerShipType>(currentIndex + 1);
		m_ShipPreview.setTextureBounds(getTextureBounds());
		m_ShipPreview.setScale({ 2.f, 2.f });
	}
}

TextureBounds ShipSelectState::getTextureBounds() const
{
	TextureBounds textureBounds;

	switch (m_CurrentShip)
	{
	case PlayerShipType::BlueRectangular:
		textureBounds.bottomLeft = glm::vec2(0.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::GreenRectangular:
		textureBounds.bottomLeft = glm::vec2(101.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::OrangeRectangular:
		textureBounds.bottomLeft = glm::vec2(202.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::RedRectangular:
		textureBounds.bottomLeft = glm::vec2(302.f, 0.f);
		textureBounds.size = glm::vec2(99.f, 75.f);
		break;
	case PlayerShipType::BluePointed:
		textureBounds.bottomLeft = glm::vec2(0.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	case PlayerShipType::GreenPointed:
		textureBounds.bottomLeft = glm::vec2(114.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	case PlayerShipType::OrangePointed:
		textureBounds.bottomLeft = glm::vec2(228.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	case PlayerShipType::RedPointed:
		textureBounds.bottomLeft = glm::vec2(342.f, 77.f);
		textureBounds.size = glm::vec2(112.f, 75.f);
		break;
	default:
		break;
	}

	return textureBounds;
}

void ShipSelectState::handleKeyRelease(SDL_Keycode key)
{

}

void ShipSelectState::update(Uint32 delta)
{
	m_MouseRect.position = Mouse::getPosition();
}

void ShipSelectState::render()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_SpriteRenderer.render(m_ShipPreview, TextureManager::getInstance().getTexture("Player"));
	m_SpriteRenderer.render(m_Sprites, TextureManager::getInstance().getTexture("ShipSelectSheet"));
}

void ShipSelectState::leftButtonPressed()
{
	if (Collision::isColliding(m_MouseRect, m_LeftRect))
		previousShip();
	else if (Collision::isColliding(m_MouseRect, m_RightRect))
		nextShip();
	else if (Collision::isColliding(m_MouseRect, m_SelectRect))
		StateManager::getInstance().push(std::make_shared<PlayState>(m_CurrentShip));
}