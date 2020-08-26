#include "map.h"
#include "aicrazy.h"
#include "newgamestate.h"

namespace DataModel {

	Map::Map(std::shared_ptr<Ressources::Manager> ressources)
		:  m_ressources(ressources),
		m_player1(ressources->getTexture("players"), sf::IntRect(0, 0, 32, 45), sf::Vector2i(-300, -300), 1),
		m_player2(ressources->getTexture("players"), sf::IntRect(0, 45, 32, 45), sf::Vector2i(-300, -300), 2),
		m_player3(ressources->getTexture("players"), sf::IntRect(0, 90, 32, 45), sf::Vector2i(-300, -300), 3),
		m_player4(ressources->getTexture("players"), sf::IntRect(0, 135, 32, 45), sf::Vector2i(-300, -300), 4) {
			m_players.push_back(&m_player1);
			m_players.push_back(&m_player2);
			m_players.push_back(&m_player3);
			m_players.push_back(&m_player4);
			resetMap();
	}

	void Map::draw(sf::RenderTexture& renderTexture) {
		//TODO DOUBLE CHECK
		for(std::size_t i = 0, iSize = m_array.size(); i != iSize; ++i) {
			for(std::size_t j = 0, jSize = m_array[i].size(); j != jSize; ++j) {
				m_array[i][j].draw(renderTexture);
			}
		}
		for(auto it = m_bombs.begin(), end = m_bombs.end(); it != end; ++it) {
			(*it)->draw(renderTexture);
		}
		for(auto it = m_powerUps.begin(), end = m_powerUps.end(); it != end; ++it) {
			(*it)->draw(renderTexture);
		}
	}

	void Map::drawPlayer(sf::RenderTexture& renderTexture) {
		for(auto it = m_players.begin(), end = m_players.end(); it != end; ++it) {
			if(!(*it)->isDead()) {
				(*it)->draw(renderTexture);
			}
		}
	}

	void Map::resetMap() {
		for (std::size_t i = 0, iSize = m_array.size(); i != iSize; ++i) {
			for (std::size_t j = 0, jSize = m_array[i].size(); j != jSize; ++j) {
				Tile tile(sf::Vector2i(static_cast<int>(i), static_cast<int>(j)));
				tile.setTexture(Tile::Ground, m_ressources);
				m_array[i][j] = tile;
			}
		}
		for(auto it = m_players.begin(), end = m_players.end(); it != end; ++it) {
			(*it)->setPosition(sf::Vector2i(-300, -300));
		}
	}

	void Map::setTile(Tile::Type type, const sf::Vector2i& position) {
		Tile tile(position);
		switch(type) {
		case Tile::Ground:
			tile.setTexture(Tile::Ground, m_ressources);
			break;
		case Tile::Grass:
			tile.setTexture(Tile::Grass, m_ressources);
			break;
		case Tile::Wall:
			tile.setTexture(Tile::Wall, m_ressources);
			break;
		case Tile::Brick:
			tile.setTexture(Tile::Brick, m_ressources);
			break;
		}
		m_array[position.x][position.y] = tile;
	}

	DataModel::Tile& Map::getTile(const sf::Vector2i& position) {
		return m_array[position.x][position.y];
	}

	std::string& Map::getName() {
		return m_name;
	}

	void Map::setName(const std::string& name) {
		m_name = name;
	}

	void Map::updateTileTexture() {
		for (std::size_t i = 0, iSize = m_array.size(); i != iSize; ++i) {
			for (std::size_t j = 0, jSize = m_array[i].size(); j != jSize; ++j) {
				m_array[i][j].setTexture(m_ressources);
			}
		}
		for(unsigned int i = 0; i < m_players.size(); ++i) {
			m_players[i]->setTexture(m_ressources->getTexture("players"), sf::IntRect(0, i*45, 32, 45));
		}
	}

	void Map::setPlayerPosition(int player, sf::Vector2i position) {
		m_players[player]->setPosition(position);
	}

	DataModel::Player& Map::getPlayer(std::size_t index) {
		return *m_players[index];
	}

	void Map::update(States::PlayingState &ownerState) {
		for(auto it = m_players.begin(), end = m_players.end(); it != end; ++it) {
			verifyPlayerCollisionPowerUp(*(*it), ownerState);
		}

		std::vector<DataModel::BombPtr> bombsToDelete;
		std::vector<DataModel::PowerUpPtr> powerUpToDelete;
		for(auto it = m_bombs.begin(), end = m_bombs.end(); it != end; ++it) {
			(*it)->update();
			if((*it)->hasExplosed()) {
				bombsToDelete.push_back((*it));
				ownerState.verifyExplosionCollision((*it)->getLevel(), (*it)->getPosition(), (*it)->getOwner());
			}
		}

		for(auto it = m_powerUps.begin(), end = m_powerUps.end(); it != end; ++it) {
			(*it)->update();
			if((*it)->isGone()) {
				powerUpToDelete.push_back((*it));
			}
		} 

		for(auto it = bombsToDelete.begin(), end = bombsToDelete.end(); it != end; ++it) {
			m_bombs.erase(std::remove(m_bombs.begin(), m_bombs.end(), (*it)), m_bombs.end());
		}

		for(auto it = powerUpToDelete.begin(), end = powerUpToDelete.end(); it != end; ++it) {
			m_powerUps.erase(std::remove(m_powerUps.begin(), m_powerUps.end(), (*it)), m_powerUps.end());
		}

		for(unsigned int i = 0; i < m_players.size(); ++i) {
			if(!m_players[i]->isDead()) {
				m_players[i]->update(*this);
			}
		}
	}

	void Map::placeBomb(Bomb::BombColor color, sf::Vector2i position, unsigned int level) {
		unsigned int y = 0;
		switch(color) {
		case Bomb::Black:
			y = 1;
			break;
		case Bomb::Red:
			y = 2;
			break;
		case Bomb::Blue:
			y= 3;
			break;
		}
		m_bombs.push_back(DataModel::BombPtr(new DataModel::Bomb(m_ressources->getTexture("bombs"), 
																 sf::IntRect(2*32, y*32, 32, 32), 
																 position, 
																 level, 
																 y+1)));
	}

	void Map::placePowerUp(DataModel::PowerUpType type, sf::Vector2i position) {
		switch(type) {
		case DataModel::Fire:
			m_powerUps.push_back(DataModel::PowerUpPtr(
				new DataModel::PowerUp(m_ressources->getTexture("items"),
									   sf::IntRect(1*32, 0*32, 32, 32),
									   position,
									   type)));
			break;
		case DataModel::BombQuantity:
			m_powerUps.push_back(DataModel::PowerUpPtr(
				new DataModel::PowerUp(m_ressources->getTexture("items"),
									   sf::IntRect(0*32, 0*32, 32, 32),
									   position,
									   type)));
			break;
		}
	}

	void Map::verifyPlayerCollisionPowerUp(DataModel::Player& player, States::PlayingState &ownerState) {
		std::vector<DataModel::PowerUpPtr> toDelete;
		for(auto it = m_powerUps.begin(), end= m_powerUps.end(); it != end; ++it) {
			if((*it)->getPosition() == player.getPosition()) {
				if((*it)->getType() == DataModel::Fire) {
					player.raiseFire();
				} else {
					player.raiseBombQuantity();
				}
				
				if(player.getId() == 1) {
					ownerState.raiseScore(States::PlayingState::POWERUP_SCORE);
				}
				toDelete.push_back((*it));
			}
		}

		for(auto it = toDelete.begin(), end = toDelete.end(); it != end; ++it) {
			m_powerUps.erase(std::remove(m_powerUps.begin(), m_powerUps.end(), (*it)), m_powerUps.end());
		}
	}

	std::vector<DataModel::PowerUpPtr>& Map::getPowerUpList() {
		return m_powerUps;
	}

	std::vector<DataModel::BombPtr>& Map::getBombList() {
		return m_bombs;
	}

	void Map::clear() {
		m_bombs.clear();
		m_powerUps.clear();
	}

	/* AStar Implementation */

	float Map::heuristic(Position start, Position end) {
		return std::sqrt(static_cast<float>((start.first-end.first)*(start.first-end.first) + (start.second-end.second)*(start.second-end.second)));
	}

	bool Map::inList(Position pos, NodeSet& n) {
		NodeSet::iterator it = n.find(pos);
	if(it == n.end())
		return false;
	else
		return true;
	}

	void Map::addNeighborNodes(Position& nodePos, Position& endPoint) {
		Tile tmp;

		//TODO DOUBLE CHECK
		for(int i = nodePos.first-1; i <= nodePos.first+1; ++i) {
			if(i < 0 || i > m_array.size()-1) //Out of bounds
				continue;

			for(int j = nodePos.second-1; j <= nodePos.second+1; ++j) {
				if(j < 0 || j > m_array[i].size() -1) //Out of bounds
					continue;
				if(i == nodePos.first && j == nodePos.second) //Current node
					continue;

				if(m_array[i][j].getProperty() & Tile::NotWalkable) //Wall, can't walk
					continue;

				Position pos(i, j);

				//Not yet inspected
				if(!inList(pos, m_closedSet)) {
					//Calculation of g h and f and parent assignement for path reconstruction
					tmp.g = m_closedSet[nodePos].g + heuristic(pos, nodePos);
					tmp.h = heuristic(pos, endPoint);
					tmp.f = tmp.g + tmp.h;
					tmp.parent = nodePos;
	
					//Will be inspected?
					if(inList(pos, m_openSet)) {
						//If the new one is better than the old one, we'll replace
						if(tmp.f < m_openSet[pos].f) {
							m_openSet[pos] = tmp;
						}
					} else { //Otherwise, we register the node in the openset for further evaluation
						m_openSet[Position(i,j)] = tmp;
					}
				}
			}
		}
	}

	Position Map::bestNode(NodeSet& n) {
		float f = n.begin()->second.f;
		Position nodePos = n.begin()->first;

		for(NodeSet::iterator it = n.begin(); it != n.end(); ++it) {
			if(it->second.f < f) {
				f = it->second.f;
				nodePos = it->first;
			}
		}

		return nodePos;
	}

	void Map::addToClosedSet(Position& pos) {
		//We take the tile of the openset at the position and put it in the closed set and then remove it from openset
		Tile& tile = m_openSet[pos];
		m_closedSet[pos] = tile;

		m_openSet.erase(pos);
	}

	void Map::reconstructPath(Position start, Position end) {
		//Starting with last node in the closed set
		Tile& tmp = m_closedSet[end];

		sf::Vector2i n;
		Position before;
		n.x = end.first;
		n.y = end.second;
		before = tmp.parent;
		m_finalPath.push_front(n);

		//We walk our way backward from the end to the beginning
		//m_finalPath is a list, and we push_front to put the node in the front, not at the back
		while(before != start) {
			n.x = before.first;
			n.y = before.second;
			m_finalPath.push_front(n);

			tmp = m_closedSet[tmp.parent];
			before = tmp.parent;
		}
	}

	std::list<sf::Vector2i> Map::runAStar(Position start, Position end) {
		//Final position
		sf::Vector2i endingPosition;
		endingPosition.x = end.first;
		endingPosition.y = end.second;

		//Starting node
		Tile startingTile;
		startingTile.parent.first = start.first;
		startingTile.parent.second = start.second;

		//Current selected node
		Position current;
		current.first = startingTile.parent.first;
		current.second = startingTile.parent.second;

		//Clearing the maps and list to make sure we get a clear shot
		m_openSet.clear();
		m_closedSet.clear();
		m_finalPath.clear();

		//We add the start in the open set, we look at the nodes around and put it in closed set
		m_openSet[current] = startingTile;
		addToClosedSet(current);
		addNeighborNodes(current, end);

		/** If the current position's is equal to the final one, we're done
		 * If the open set is empty, we're done
		 **/
		while(!((current.first == endingPosition.x) && (current.second == endingPosition.y)) && (!m_openSet.empty())) {
			/** For every node in the open set we select the best node available
			 * We then add the nodes to the closed set
			 * And we add all neighbor nodes to that one in the openset
			 **/
			current = bestNode(m_openSet);
			addToClosedSet(current);
			addNeighborNodes(current, end);
		}

		//If current is the end we've been searching, hooray found a path. Else, no solution
		if(current == end) {
			reconstructPath(start, end); //we recreate the path from the end to the start

			return m_finalPath;
		} else { //No solution
			return std::list<sf::Vector2i>();
		}
	}
}