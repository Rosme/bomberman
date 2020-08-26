#include "powerup.h"

namespace DataModel {

	PowerUp::PowerUp()
		: m_type(DataModel::BombQuantity) {}

	PowerUp::PowerUp(sf::Texture& texture, sf::IntRect subRect, sf::Vector2i position, PowerUpType type)
		: GameObject(texture, subRect, position), m_lifeTimer(sf::milliseconds(5000)), m_type(type) {
		m_lifeTimer.start();
	}

	DataModel::PowerUpType PowerUp::getType() const {
		return m_type;
	}

	bool PowerUp::isGone() const {
		return m_lifeTimer.isExpired();
	}
}