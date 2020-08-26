#ifndef DATAMODEL_MAP_H
#define DATAMODEL_MAP_H

#include <list>
#include <map>
#include <memory>
#include <array>
#include <cereal/access.hpp>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "ressourcesmanager.h"
#include "player.h"
#include "bomb.h"
#include "powerup.h"

namespace States {
	class PlayingState;
}

namespace DataModel {

	class Map {
		/* For serialization into file */
		friend class cereal::access;

		
		template<class Archive>
		void save(Archive & ar, const std::uint32_t /* file version */) const {
			ar(m_array.size());
			ar(m_array[0].size());
			for(std::size_t i = 0; i < m_array.size(); ++i) {
				for(std::size_t j = 0; j < m_array[i].size(); ++j) {
					ar(m_array[i][j]);
				}
			}
			ar(m_name);
			ar(m_player1);
			ar(m_player2);
			ar(m_player3);
			ar(m_player4);
		}

		template<class Archive>
		void load(Archive& ar, const std::uint32_t /* file version */) {
			std::size_t height;
			std::size_t width;
			ar(height);
			ar(width);
			for (std::size_t i = 0; i < m_array.size(); ++i) {
				for (std::size_t j = 0; j < m_array[i].size(); ++j) {
					ar(m_array[i][j]);
				}
			}
			ar(m_name);
			m_player1 = Player{};
			m_player2 = Player{};
			m_player3 = Player{};
			m_player4 =	Player{};
			ar(m_player1);
			ar(m_player2);
			ar(m_player3);
			ar(m_player4);
			m_players = {&m_player1, &m_player2, &m_player3, &m_player4};
		}
	private:
		typedef std::array<std::array<Tile, 21>, 27> MapArray;
		//typedef rsm::Matrix<Tile> MapArray;
		MapArray m_array;
		std::shared_ptr<Ressources::Manager> m_ressources;
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
		Map(std::shared_ptr<Ressources::Manager> ressources);

		void clear(); //Clear the map of all power up and bombs
		void draw(sf::RenderTexture& renderTexture); //Draw the map
		void drawPlayer(sf::RenderTexture& renderTexture); //Draw the player
		std::vector<DataModel::BombPtr>& getBombList(); //Return all the bombs on the map
		std::string& getName(); //Return the name of the map
		DataModel::Player& getPlayer(std::size_t index); //Return the player
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