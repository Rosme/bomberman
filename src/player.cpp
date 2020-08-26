#include "player.h"
#include "map.h"

namespace DataModel {

	const unsigned char Player::MAX_BOMB_LEVEL = 4;
	const unsigned char Player::MAX_BOMB_QUANTITY = 5;

	Player::Player()
		: GameObject(), 
		m_bombLevel(1), 
		m_moveTimer(sf::milliseconds(150), true), 
		m_maxBomb(1), 
		m_currentBombQty(0),
		m_bombPlaceTimer(sf::milliseconds(150), true),
		m_bombsTimer(m_maxBomb),
		m_lifes(3),
		m_strategie(nullptr),
		m_id(1) {
			m_bombsTimer[0].restart(sf::milliseconds(0), true);
	}

	Player::Player(sf::Texture& texture, sf::IntRect subRect, sf::Vector2i position, unsigned int id)
		: GameObject(texture, subRect, position), 
		m_bombLevel(1), 
		m_moveTimer(sf::milliseconds(150), true), 
		m_maxBomb(1), 
		m_currentBombQty(0),
		m_bombPlaceTimer(sf::milliseconds(150), true),
		m_bombsTimer(m_maxBomb),
		m_lifes(3),
		m_strategie(nullptr),
		m_id(id) {
			m_bombsTimer[0].restart(sf::milliseconds(0), true);
			updateSpritePosition(0, -13);
	}

	bool Player::canPlaceBomb() const {
		if(m_bombPlaceTimer.isExpired()) {
			return (m_currentBombQty < m_maxBomb);
		}
		return false;
	}

	unsigned int Player::getBombLevel() const {
		return m_bombLevel;
	}

	unsigned int Player::getBombQuantity() const {
		return (m_maxBomb - m_currentBombQty);
	}

	unsigned int Player::getId() const {
		return m_id;
	}

	unsigned int Player::getRemainingLife() const {
		return m_lifes;
	}

	bool Player::isDead() const {
		return m_lifes == 0;
	}

	void Player::move(Player::Move direction) {
		if(m_moveTimer.isExpired()) {
			if(direction == Player::Up) {
				--m_position.y;
				sf::IntRect textRect = m_sprite.getTextureRect();
				textRect.left = 2*32;
				m_sprite.setTextureRect(textRect);
			}
			if(direction == Player::Down) {
				++m_position.y;
				sf::IntRect textRect = m_sprite.getTextureRect();
				textRect.left = 0*32;
				m_sprite.setTextureRect(textRect);
			}
			if(direction == Player::Left) {
				--m_position.x;
				sf::IntRect textRect = m_sprite.getTextureRect();
				textRect.left = 1*32;
				m_sprite.setTextureRect(textRect);
			}
			if(direction == Player::Right) {
				++m_position.x;
				sf::IntRect textRect = m_sprite.getTextureRect();
				textRect.left = 3*32;
				m_sprite.setTextureRect(textRect);
			}

			updateSpritePosition(0, -13);
			m_moveTimer.restart(true);
		}
	}

	void Player::placeBomb() {
		++m_currentBombQty;
		m_bombPlaceTimer.restart(true);
		for(unsigned int i = 0; i < m_bombsTimer.size(); ++i) {
			if(m_bombsTimer[i].isExpired()) {
				m_bombsTimer[i].restart(sf::milliseconds(3000), true);
			}
		}
	}

	void Player::raiseBombQuantity() {
		m_maxBomb = (m_maxBomb < MAX_BOMB_QUANTITY) ? m_maxBomb+1: m_maxBomb;
		//In case we get another bomb booster but we've reached max, we don't want to add a timer
		if(m_maxBomb > m_bombsTimer.size()) {
			m_bombsTimer.push_back(Utils::Timer(sf::milliseconds(0)));
		}
	}

	void Player::raiseFire() {
		m_bombLevel = (m_bombLevel < MAX_BOMB_LEVEL) ? m_bombLevel+1 : m_bombLevel;
	}

	void Player::removeBomb() {
		--m_currentBombQty;
	}

	void Player::removeLife() {
		m_lifes = (m_lifes > 0) ? --m_lifes : m_lifes;
	}

	void Player::setId(unsigned int id) {
		m_id = id;
	}

	void Player::setPosition(sf::Vector2i position) {
		m_position = position;
		updateSpritePosition(0, -13);
	}

	void Player::setStrategie(AIStrategie* strategie) {
		m_strategie.reset(strategie);
	}

	void Player::update(DataModel::Map& map) {
		if(m_currentBombQty > 0) {
			for(unsigned int i = 0; i < m_bombsTimer.size(); ++i) {
				if(m_bombsTimer[i].isExpired()) {
					removeBomb();
				}
			}
		}

		if(m_strategie.get()) {
			m_strategie->update(map, *this);
		}
	}
}