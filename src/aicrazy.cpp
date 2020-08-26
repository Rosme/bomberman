#include "aicrazy.h"
#include "map.h"

namespace DataModel {

	AICrazy::AICrazy()
		: AIStrategie(),
		m_currentDecision(Decision::MoveUp),
		m_decisionTimer(sf::milliseconds(DECISION_LIMIT), true),
		  m_gen(static_cast<unsigned int>(time(nullptr)))
		   {
		m_decisions[0] = AICrazy::MoveUp;
		m_decisions[1] = AICrazy::MoveDown;
		m_decisions[2] = AICrazy::MoveLeft;
		m_decisions[3] = AICrazy::MoveRight;
		m_decisions[4] = AICrazy::DropBomb;
	}


	void AICrazy::update(DataModel::Map& map, DataModel::Player& owner) {
		if(m_decisionTimer.isExpired()) {
			//MoveUp, MoveDown, MoveLeft, MoveRight, DropBomb
			std::discrete_distribution<> dist({ 0.22, 0.22, 0.22, 0.22, 0.12 });

			Decision decision = m_decisions[dist(m_gen)];
			while(decision == m_currentDecision) {
				decision = m_decisions[dist(m_gen)];
			}
			m_currentDecision = decision;

			m_decisionTimer.restart(sf::milliseconds(DECISION_LIMIT), true);
		}

		auto tilePosition = owner.getPosition();
		switch(m_currentDecision) {
		case MoveUp:
			--tilePosition.y;
			if(map.getTile(tilePosition).getProperty() & DataModel::Tile::Walkable) {
				owner.move(DataModel::Player::Up);
			}
			break;
		case MoveDown:
			++tilePosition.y;
			if(map.getTile(tilePosition).getProperty() & DataModel::Tile::Walkable) {
				owner.move(DataModel::Player::Down);
			}
			break;
		case MoveLeft:
			--tilePosition.x;
			if(map.getTile(tilePosition).getProperty() & DataModel::Tile::Walkable) {
				owner.move(DataModel::Player::Left);
			}
			break;
		case MoveRight:
			++tilePosition.x;
			if(map.getTile(tilePosition).getProperty() & DataModel::Tile::Walkable) {
				owner.move(DataModel::Player::Right);
			}
			break;
		case DropBomb:
			if(owner.canPlaceBomb()) {
				owner.placeBomb();
				map.placeBomb(Bomb::Blue, owner.getPosition(), owner.getBombLevel());
				m_decisionTimer.restart(sf::milliseconds(20), true);
			}
			break;
		}
	}
}