#ifndef DATAMODEL_TILE_H
#define DATAMODEL_TILE_H

#include <memory>
#include <cereal/access.hpp>
#include <SFML/Graphics.hpp>

#include "ressourcesmanager.h"

namespace DataModel {
	typedef std::pair<int, int> Position;
	class Tile {
		/* For serialization into file */
		friend class cereal::access;

		template<class Archive>
		void serialize(Archive & ar, const std::uint32_t/* file version */) {
			ar(m_mapPosition.x);
			ar(m_mapPosition.y);
			ar(m_properties);
			ar(m_type);
		}
	public:
		enum Type {
			Ground,
			Grass,
			Wall,
			Brick
		};
		enum Property {
			Walkable = (1<<0),
			NotWalkable = (1<<1),
			Destructible = (1<<2),
			Indestructible = (1<<3)
		};
	private:
		sf::Vector2i m_mapPosition;
		sf::Sprite m_sprite;
		Property m_properties;
		Type m_type;

	public:
		static const unsigned int SIZE;

		Tile();
		Tile(sf::Vector2i position);

		void draw(sf::RenderTexture& renderTexture); //Draw the tile
		Property getProperty() const; //Return its properties
		void setTexture(Type type, std::shared_ptr<Ressources::Manager> ressources); //Set the texture for sprite
		void setTexture(std::shared_ptr<Ressources::Manager> ressources); //Set the texture for sprite

		/* A* Algo Data */
		Position parent;
		float f, g, h;
	};

}

#endif