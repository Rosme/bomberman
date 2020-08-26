#ifndef OPTIONS_OPTION_H
#define OPTIONS_OPTION_H

#include <cereal/access.hpp>
#include <SFML/Window.hpp>

namespace Options {

	/* Enum for the different key use in the game */
	enum GameKey {
		Up,
		Down,
		Left,
		Right,
		Pause,
		Bomb
	};

	class Option {
		/* For serialization into file */
		friend class cereal::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file version */) {
			ar(m_upKey);
			ar(m_downKey);
			ar(m_leftKey);
			ar(m_rightKey);
			ar(m_pauseKey);
			ar(m_bombKey);
		}

	private:
		sf::Keyboard::Key m_upKey,
						  m_downKey,
						  m_leftKey,
						  m_rightKey,
						  m_pauseKey,
						  m_bombKey;
	public:
		/* Ctor */
		Option();

		/* Methods */
		sf::Keyboard::Key getKey(const Options::GameKey) const; //Returns the key value of the game key
		void setKey(const Options::GameKey gKey, const sf::Keyboard::Key key); //Set the value for a game key
	};

}

#endif