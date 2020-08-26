#include <algorithm>
#include <vector>
#include "aidefensive.h"
#include "map.h"

namespace DataModel {

	AIDefensive::AIDefensive()
		: AIStrategie(), m_changePathTimer(sf::milliseconds(100), true), m_decisionTimer(sf::milliseconds(DECISION_LIMIT), true) {}

	sf::Vector2i AIDefensive::findBestPosition(DataModel::Map& map, sf::Vector2i ownPos, sf::Vector2i runPos) {
		sf::Vector2i bestPosition(-1, -1);
		if((runPos.x < ownPos.x && runPos.y < ownPos.y) || (runPos.x == ownPos.x && runPos.y < ownPos.y)) {
			for(unsigned int i = 26; i > 13; --i) {
				for(unsigned int j = 20; j > 11; --j) {
					if(map.getTile(sf::Vector2i(i, j)).getProperty() & Tile::Walkable) {
						bestPosition.x = i;
						bestPosition.y = j;
						break;
					}
				}
			}
		} else if((runPos.x < ownPos.x && runPos.y > ownPos.y) || (runPos.x == ownPos.x && runPos.y > ownPos.y)) {
			for(unsigned int i = 26; i > 13; --i) {
				for(unsigned int j = 1; j < 11; ++j) {
					if(map.getTile(sf::Vector2i(i, j)).getProperty() & Tile::Walkable) {
						bestPosition.x = i;
						bestPosition.y = j;
						break;
					}
				}
			}
		} else if((runPos.x > ownPos.x && runPos.y < ownPos.y) || (runPos.x > ownPos.x && runPos.y == ownPos.y)) {
			for(unsigned int i = 1; i < 13; ++i) {
				for(unsigned int j = 20; j > 11; --j) {
					if(map.getTile(sf::Vector2i(i, j)).getProperty() & Tile::Walkable) {
						bestPosition.x = i;
						bestPosition.y = j;
						break;
					}
				}
			}
		} else {
			for(unsigned int i = 1; i < 13; ++i) {
				for(unsigned int j = 1; j < 11; ++j) {
					if(map.getTile(sf::Vector2i(i, j)).getProperty() & Tile::Walkable) {
						bestPosition.x = i;
						bestPosition.y = j;
						break;
					}
				}
			}
		}

		return bestPosition;
	}

	AIStrategie::Path AIDefensive::getPath(DataModel::Map& map, DataModel::Player& owner) {
		sf::Vector2i ownPos = owner.getPosition();
		auto powerUpList = map.getPowerUpList();
		if(powerUpList.size() > 0) {
			PathList powerUpPaths;

			for(auto it = powerUpList.begin(), end = powerUpList.end(); it != end; ++it) {
				powerUpPaths.push_back(map.runAStar(std::make_pair(ownPos.x, ownPos.y),
													std::make_pair((*it)->getPosition().x, (*it)->getPosition().y)));
			}

			return *std::min_element(powerUpPaths.begin(), powerUpPaths.end(), PathFinder());
		}

		sf::Vector2i bestPosition(-1, -1);

		//No power Up, let's verify the bombs
		auto bombList = map.getBombList();
		if(bombList.size() > 0) {
			PathList bombPaths;

			for(auto it = bombList.begin(), end = bombList.end(); it != end; ++it) {
				bombPaths.push_back(map.runAStar(std::make_pair(ownPos.x, ownPos.y),
												 std::make_pair((*it)->getPosition().x, (*it)->getPosition().y)));
			}

			auto bestPath = std::min_element(bombPaths.begin(), bombPaths.end(), PathFinder());

			if(bestPath->size() < 5) {
				bestPosition = findBestPosition(map, ownPos, bestPath->back());
			}
		}

		//No bomb in proximity, let's run from the players
		sf::Vector2i player1Pos = map.getPlayer(0).getPosition(),
					 player2Pos = map.getPlayer(1).getPosition(),
					 player4Pos = map.getPlayer(3).getPosition();
		PathList playersPath;
		playersPath.push_back(map.runAStar(std::make_pair(ownPos.x, ownPos.y), std::make_pair(player1Pos.x, player1Pos.y)));
		if(!map.getPlayer(1).isDead()) {
			playersPath.push_back(map.runAStar(std::make_pair(ownPos.x, ownPos.y), std::make_pair(player2Pos.x, player2Pos.y)));
		}
		if(!map.getPlayer(2).isDead()) {
			playersPath.push_back(map.runAStar(std::make_pair(ownPos.x, ownPos.y), std::make_pair(player4Pos.x, player4Pos.y)));
		}


		auto closestPlayer = std::min_element(playersPath.begin(), playersPath.end(), PathFinder());

		if(bestPosition.x == -1 && bestPosition.y == -1) {
			bestPosition = findBestPosition(map, ownPos, closestPlayer->back());
		}

		return map.runAStar(std::make_pair(ownPos.x, ownPos.y), std::make_pair(bestPosition.x, bestPosition.y));
	}

	void AIDefensive::update(DataModel::Map& map, DataModel::Player& owner) {
		if(m_decisionTimer.isExpired()) {
			if(m_changePathTimer.isExpired() || m_currentPath.size() == 0) {
				if(m_currentPath.size() != 0 && owner.canPlaceBomb()) {
					owner.placeBomb();
					map.placeBomb(DataModel::Bomb::Red, owner.getPosition(), owner.getBombLevel());
				}
				m_currentPath = getPath(map, owner);
				m_changePathTimer.restart(true);
			}

			sf::Vector2i ownPos = owner.getPosition();
			sf::Vector2i nextTilePosition = *(m_currentPath.begin()++);
			//The A* calculate with diagonals. Can't move that way in game
			//If the next tile is in a diagonal, we'll find another tile to move.
			if(nextTilePosition.x != ownPos.x && nextTilePosition.y != ownPos.y) {
				bool valid = false;
				if(nextTilePosition.x < ownPos.x) {
					sf::Vector2i t = nextTilePosition;
					++t.x;
					if(map.getTile(t).getProperty() & DataModel::Tile::Walkable) {
						nextTilePosition = t;
						valid = true;
					}
				} else if(nextTilePosition.x > ownPos.x) {
					sf::Vector2i t = nextTilePosition;
					--t.x;
					if(map.getTile(t).getProperty() & DataModel::Tile::Walkable) {
						nextTilePosition = t;
						valid = true;
					}
				}

				if(!valid) {
					if(nextTilePosition.y < ownPos.y) {
						sf::Vector2i t = nextTilePosition;
						++t.y;
						if(map.getTile(t).getProperty() & DataModel::Tile::Walkable) {
							nextTilePosition = t;
						}
					} else if(nextTilePosition.y > ownPos.y) {
						sf::Vector2i t = nextTilePosition;
						--t.y;
						if(map.getTile(t).getProperty() & DataModel::Tile::Walkable) {
							nextTilePosition = t;
						}
					}
				}
			}

			if(nextTilePosition.x < ownPos.x) {
				sf::Vector2i t = nextTilePosition;
				--t.x;
				owner.move(Player::Left);
			} else if(nextTilePosition.x > ownPos.x) {
				sf::Vector2i t = nextTilePosition;
				++t.x;
				owner.move(Player::Right);
			} 
			if(nextTilePosition.y < ownPos.y) {
				sf::Vector2i t = nextTilePosition;
				--t.y;
				owner.move(Player::Up);
			} else if(nextTilePosition.y > ownPos.y) {
				sf::Vector2i t = nextTilePosition;
				++t.y;
				owner.move(Player::Down);
			}

			m_decisionTimer.restart(true);
		}
	}
}