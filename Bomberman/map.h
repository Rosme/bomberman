#ifndef DATAMODEL_MAP_H
#define DATAMODEL_MAP_H

#include <list>
#include <map>
#include <boost/multi_array.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/smart_ptr.hpp>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "ressourcesmanager.h"
#include "serial_multi_array.h"
#include "player.h"
#include "bomb.h"
#include "powerup.h"

namespace States {
	class PlayingState;
}

namespace DataModel {

	class Map {
		/* For serialization into file */
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file version */) {
			ar & BOOST_SERIALIZATION_NVP(m_array);
			ar & BOOST_SERIALIZATION_NVP(m_name);
			ar & BOOST_SERIALIZATION_NVP(m_players);
		}
	private:
		typedef boost::multi_array<Tile, 2> MapArray;
		MapArray m_array;
		boost::shared_ptr<Ressources::Manager> m_ressources;
		DataModel::Player m_player1;
		DataModel::Player m_player2;
		DataModel::Player m_player3;
		DataModel::Player m_player4;
		std::string m_name;
		std::vector<DataModel::Player*> m_players;
		std::vector<DataModel::BombPtr> m_bombs;
		std::vector<DataModel::PowerUpPtr> m_powerUps;

		void verifyPlayerCollisionPowerUp(DataModel::Player& player, States::PlayingState &ownerState);

		/* A* Algorithm to find path */
		typedef std::map<Position, Tile> NodeSet;
		NodeSet m_closedSet,
			    m_openSet;
		std::list<sf::Vector2i> m_finalPath;

		float heuristic(Position start, Position end);
		bool inList(Position pos, NodeSet& n);
		void addNeighborNodes(Position& nodePos, Position& endPoint);
		Position bestNode(NodeSet& n);
		void addToClosedSet(Position& pos);
		void reconstructPath(Position start, Position end);

	public:
		Map(boost::shared_ptr<Ressources::Manager> ressources);

		void clear(); //Clear the map of all power up and bombs
		void draw(sf::RenderTexture& renderTexture); //Draw the map
		void drawPlayer(sf::RenderTexture& renderTexture); //Draw the player
		std::vector<DataModel::BombPtr>& getBombList(); //Return all the bombs on the map
		std::string& getName(); //Return the name of the map
		DataModel::Player& getPlayer(int index); //Return the player
		std::vector<DataModel::PowerUpPtr>& getPowerUpList(); //return all the power ups on the map
		DataModel::Tile& getTile(const sf::Vector2i& position); //Return the tile at the position
		void placeBomb(Bomb::BombColor color, sf::Vector2i position, unsigned int level); //Place a bomb on the map
		void placePowerUp(DataModel::PowerUpType type, sf::Vector2i position); //Place a power up on the map
		void resetMap(); //Reset the map to the gray ground
		void setName(const std::string& name); //Set the map name
		void setPlayerPosition(int player, sf::Vector2i position); //Set the player position
		void setTile(Tile::Type type, const sf::Vector2i& position); //Set the type of tile
		void update(States::PlayingState &ownerState); //Update the map state
		void updateTileTexture(); //Update the texture of the tiles
 
		/* AStar Access */
		std::list<sf::Vector2i> runAStar(Position start, Position end);
	};

}

#endif