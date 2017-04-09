#include "bomb.h"

namespace DataModel {

	Bomb::Bomb()
		: m_level(1), m_owner(1) {}

	Bomb::Bomb(sf::Texture& texture, sf::IntRect subRect, sf::Vector2i position, unsigned int level, unsigned int owner)
		: GameObject(texture, subRect, position), 
		  m_timer(sf::milliseconds(3000)), 
		  m_level(level),
		  m_owner(owner) {
			m_timer.start();
		}

	unsigned int Bomb::getLevel() const {
		return m_level;
	}

	unsigned int Bomb::getOwner() const {
		return m_owner;
	}

	bool Bomb::hasExplosed() const {
		return m_timer.isExpired();
	}

	void Bomb::update() {
		if(m_timer.getRemainingTime().asMilliseconds() < 2000 && m_timer.getRemainingTime().asMilliseconds() > 1000) {
			sf::IntRect rect = m_sprite.getTextureRect();
			rect.left = 1*32;
			m_sprite.setTextureRect(rect);
		} else if(m_timer.getRemainingTime().asMilliseconds() < 1000) {
			sf::IntRect rect = m_sprite.getTextureRect();
			rect.left = 0*32;
			m_sprite.setTextureRect(rect);
		}
	}
}