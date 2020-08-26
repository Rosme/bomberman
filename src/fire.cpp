#include "fire.h"

namespace Ressources {

	Ressources::FirePtr makeFire(sf::Texture& texture, sf::IntRect textureRect, sf::Vector2i position) {
		position.x = position.x*32;
		position.y = position.y*32;
		Ressources::FirePtr fire(new Ressources::Fire());
		fire->sprite.setPosition(static_cast<sf::Vector2f>(position));
		fire->sprite.setTexture(texture);
		fire->sprite.setTextureRect(textureRect);
		fire->lifeTimer.restart(sf::milliseconds(200), true);
		return fire;
	}
}