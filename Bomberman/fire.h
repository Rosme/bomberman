#ifndef RESSOURCES_FIRE_H
#define RESSOURCES_FIRE_H

#include <boost/smart_ptr.hpp>
#include <SFML/Graphics.hpp>
#include "timer.h"

namespace Ressources {

	struct Fire {
		sf::Sprite sprite;
		Utils::Timer lifeTimer;
	};

	typedef boost::shared_ptr<Ressources::Fire> FirePtr;

	Ressources::FirePtr makeFire(sf::Texture& texture, sf::IntRect textureRect, sf::Vector2i position); //Factory, make a fire
}

#endif