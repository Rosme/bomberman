#ifndef DATAMODEL_BOMB_H
#define DATAMODEL_BOMB_H

#include <boost/smart_ptr.hpp>
#include "gameobject.h"
#include "timer.h"

namespace DataModel {

	class Bomb : public GameObject {
	private:
		Utils::Timer m_timer;
		unsigned int m_level;
		unsigned int m_owner;

	public:
		enum BombColor {
			White,
			Black,
			Red,
			Blue
		};
		Bomb();
		Bomb(sf::Texture& texture, sf::IntRect subRect, sf::Vector2i position, unsigned int level = 1, unsigned int owner = 1);

		unsigned int getLevel() const; //Get the fire level
		unsigned int getOwner() const; //Get the owner of the bomb
		bool hasExplosed() const; //BOOM! or not
		void update(); //Update sprite accordingly to timer
	};

	typedef boost::shared_ptr<DataModel::Bomb> BombPtr;
}

#endif