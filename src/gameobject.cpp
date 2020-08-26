#include "gameobject.h"

namespace DataModel {

	GameObject::GameObject()
		: m_position(-300, -300) {
			m_sprite.setPosition(-300, -300);
	}

	GameObject::GameObject(sf::Texture& texture, sf::IntRect subRect, sf::Vector2i position)
		: m_sprite(texture), m_position(position) {
			m_sprite.setTextureRect(subRect);
			updateSpritePosition();
		}

	GameObject::~GameObject() {}

	void GameObject::draw(sf::RenderTexture& renderTexture) {
		renderTexture.draw(m_sprite);
	}

	sf::Vector2i GameObject::getPosition() {
		return m_position;
	}

	void GameObject::setPosition(sf::Vector2i position) {
		m_position = position;
		updateSpritePosition();
	}

	void GameObject::setTexture(sf::Texture& texture, sf::IntRect subRect) {
		m_sprite.setTexture(texture);
		m_sprite.setTextureRect(subRect);
		setPosition(m_position);
	}

	void GameObject::update(){}

	void GameObject::updateSpritePosition(int xMargin, int yMargin) {
		m_sprite.setPosition(static_cast<float>((m_position.x*32)+xMargin), static_cast<float>((m_position.y*32)+yMargin));
	}
}