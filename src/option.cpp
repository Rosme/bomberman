#include "option.h"

namespace Options {

	Option::Option()
		: m_upKey(sf::Keyboard::W), 
		m_downKey(sf::Keyboard::S), 
		m_leftKey(sf::Keyboard::A), 
		m_rightKey(sf::Keyboard::D), 
		m_pauseKey(sf::Keyboard::Escape), 
		m_bombKey(sf::Keyboard::Space) {}

	void Option::setKey(const Options::GameKey gKey, const sf::Keyboard::Key key) {
		switch(gKey) {
		case Options::Up:
			m_upKey = key;
			break;
		case Options::Down:
			m_downKey = key;
			break;
		case Options::Left:
			m_leftKey = key;
			break;
		case Options::Right:
			m_rightKey = key;
			break;
		case Options::Pause:
			m_pauseKey = key;
			break;
		case Options::Bomb:
			m_bombKey = key;
			break;
		}
	}

	sf::Keyboard::Key Option::getKey(const Options::GameKey key) const {
		switch(key) {
		case Options::Up:
			return m_upKey;
			break;
		case Options::Down:
			return m_downKey;
			break;
		case Options::Left:
			return m_leftKey;
			break;
		case Options::Right:
			return m_rightKey;
			break;
		case Options::Pause:
			return m_pauseKey;
			break;
		case Options::Bomb:
			return m_bombKey;
			break;
		default:
			return sf::Keyboard::Unknown;
		}
	}
}