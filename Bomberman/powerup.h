#ifndef DATAMODEL_POWERUP_H
#define DATAMODEL_POWERUP_H

#include <boost/smart_ptr.hpp>
#include "gameobject.h"
#include "timer.h"

namespace DataModel {

	enum PowerUpType {
		Fire,
		BombQuantity
	};

	class PowerUp : public GameObject {
	private:
		Utils::Timer m_lifeTimer;
		PowerUpType m_type;

	public:
		PowerUp();
		PowerUp(sf::Texture& texture, sf::IntRect subRect, sf::Vector2i position, PowerUpType type);

		DataModel::PowerUpType getType() const; //What am I? Fire or Bomb?
		bool isGone() const; //Timer's done, bye bye
	};

	typedef boost::shared_ptr<DataModel::PowerUp> PowerUpPtr;
}

#endif