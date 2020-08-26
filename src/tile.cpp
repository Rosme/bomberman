#include "tile.h"

namespace DataModel {
	const unsigned int Tile::SIZE = 32;

	Tile::Tile() {}

	Tile::Tile(sf::Vector2i position)
		: m_mapPosition(position) {
		m_sprite.setPosition(static_cast<float>(m_mapPosition.x*SIZE), static_cast<float>(m_mapPosition.y*SIZE));
	}

	Tile::Property Tile::getProperty() const {
		return m_properties;
	}

	void Tile::draw(sf::RenderTexture& renderTexture) {
		renderTexture.draw(m_sprite);
	}

	void Tile::setTexture(Type type, std::shared_ptr<Ressources::Manager> ressources) {
		m_type = type;
		m_sprite.setTexture(ressources->getTexture("tiles"));
		switch(m_type) {
		case Tile::Ground:
			m_properties = Tile::Property(Tile::Walkable | Tile::Indestructible);
			m_sprite.setTextureRect(sf::IntRect(Tile::SIZE*3, Tile::SIZE*0, Tile::SIZE, Tile::SIZE));
			break;
		case Tile::Grass:
			m_properties = Tile::Property(Tile::Walkable | Tile::Indestructible);
			m_sprite.setTextureRect(sf::IntRect(Tile::SIZE*2, Tile::SIZE*0, Tile::SIZE, Tile::SIZE));
			break;
		case Tile::Wall:
			m_properties = Tile::Property(Tile::NotWalkable | Tile::Indestructible);
			m_sprite.setTextureRect(sf::IntRect(Tile::SIZE*0, Tile::SIZE*0, Tile::SIZE, Tile::SIZE));
			break;
		case Tile::Brick:
			m_properties = Tile::Property(Tile::NotWalkable | Tile::Destructible);
			m_sprite.setTextureRect(sf::IntRect(Tile::SIZE*0, Tile::SIZE*1, Tile::SIZE, Tile::SIZE));
			break;
		}
	}

	void Tile::setTexture(std::shared_ptr<Ressources::Manager> ressources) {
		m_sprite.setTexture(ressources->getTexture("tiles"));
		switch(m_type) {
		case Tile::Ground:
			m_sprite.setTextureRect(sf::IntRect(Tile::SIZE*3, Tile::SIZE*0, Tile::SIZE, Tile::SIZE));
			break;
		case Tile::Grass:
			m_sprite.setTextureRect(sf::IntRect(Tile::SIZE*2, Tile::SIZE*0, Tile::SIZE, Tile::SIZE));
			break;
		case Tile::Wall:
			m_sprite.setTextureRect(sf::IntRect(Tile::SIZE*0, Tile::SIZE*0, Tile::SIZE, Tile::SIZE));
			break;
		case Tile::Brick:
			m_sprite.setTextureRect(sf::IntRect(Tile::SIZE*0, Tile::SIZE*1, Tile::SIZE, Tile::SIZE));
			break;
		}
	}
}