#ifndef DATAMODEL_TILE_H
#define DATAMODEL_TILE_H

#include <boost/serialization/access.hpp>
#include <boost/smart_ptr.hpp>
#include <SFML/Graphics.hpp>

#include "ressourcesmanager.h"

namespace DataModel {
	typedef std::pair<int, int> Position;
	class Tile {
		/* For serialization into file */
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file version */) {
			ar & BOOST_SERIALIZATION_NVP(m_mapPosition.x);
			ar & BOOST_SERIALIZATION_NVP(m_mapPosition.y);
			ar & BOOST_SERIALIZATION_NVP(m_properties);
			ar & BOOST_SERIALIZATION_NVP(m_type);
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
		void setTexture(Type type, boost::shared_ptr<Ressources::Manager> ressources); //Set the texture for sprite
		void setTexture(boost::shared_ptr<Ressources::Manager> ressources); //Set the texture for sprite

		/* A* Algo Data */
		Position parent;
		float f, g, h;
	};

}

#endif