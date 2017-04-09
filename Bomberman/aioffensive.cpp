#include <algorithm>
#include <vector>
#include "aioffensive.h"
#include "map.h"

namespace DataModel {

	bool AIOffensive::takeSecond = false;

	AIOffensive::AIOffensive()
		: AIStrategie(),
			m_decisionTimer(sf::milliseconds(DECISION_LIMIT), true) {}

	void AIOffensive::update(DataModel::Map& map, DataModel::Player& owner) {
		if(m_decisionTimer.isExpired()) {
			sf::Vector2i player1Pos = map.getPlayer(0).getPosition(),
						 player3Pos = map.getPlayer(2).getPosition(),
						 player4Pos = map.getPlayer(3).getPosition(),
						 ownPos = owner.getPosition();

			PathList paths;
			paths.push_back(map.runAStar(std::make_pair(ownPos.x, ownPos.y), std::make_pair(player1Pos.x, player1Pos.y)));
			if(!map.getPlayer(2).isDead()) {
				paths.push_back(map.runAStar(std::make_pair(ownPos.x, ownPos.y), std::make_pair(player3Pos.x, player3Pos.y)));
			}
			if(!map.getPlayer(3).isDead()) {
				paths.push_back(map.runAStar(std::make_pair(ownPos.x, ownPos.y), std::make_pair(player4Pos.x, player4Pos.y)));
			}

			auto bestPath = std::min_element(paths.begin(), paths.end(), PathFinder());
			if(AIOffensive::takeSecond) {
				if(bestPath->size() < 10 && paths.size() > 1) {
					paths.erase(bestPath);
					bestPath = std::min_element(paths.begin(), paths.end(), PathFinder());
				} else {
					AIOffensive::takeSecond = false;
				}
			}

			bool hasPlacedBomb = false;
			bool hasMoved = false;

			if(bestPath->size() < 3) {
				if(owner.canPlaceBomb()) {
					owner.placeBomb();
					map.placeBomb(DataModel::Bomb::Black, owner.getPosition(), owner.getBombLevel());
					hasPlacedBomb = true;
				}
			}

			sf::Vector2i nextTilePosition = *(bestPath->begin()++);
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
				hasMoved = true;
			} else if(nextTilePosition.x > ownPos.x) {
				sf::Vector2i t = nextTilePosition;
				++t.x;
				owner.move(Player::Right);
				hasMoved = true;
			} 
			if(nextTilePosition.y < ownPos.y) {
				sf::Vector2i t = nextTilePosition;
				--t.y;
				owner.move(Player::Up);
				hasMoved = true;
			} else if(nextTilePosition.y > ownPos.y) {
				sf::Vector2i t = nextTilePosition;
				++t.y;
				owner.move(Player::Down);
				hasMoved = true;
			}

			if(hasPlacedBomb && !hasMoved) {
				AIOffensive::takeSecond = true;
				sf::Vector2i newPosition = owner.getPosition();
				if(ownPos.x < newPosition.x) {
					owner.move(Player::Left);
				} else if(ownPos.x > newPosition.x) {
					owner.move(Player::Right);
				}
				if(ownPos.y < newPosition.y) {
					owner.move(Player::Up);
				} else if(ownPos.y > newPosition.y) {
					owner.move(Player::Down);
				}
			}

			m_decisionTimer.restart(true);
		}
	}

}