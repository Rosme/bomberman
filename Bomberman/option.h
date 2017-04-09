#ifndef OPTIONS_OPTION_H
#define OPTIONS_OPTION_H

#include <boost/serialization/access.hpp>
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
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file version */) {
			ar & BOOST_SERIALIZATION_NVP(m_upKey);
			ar & BOOST_SERIALIZATION_NVP(m_downKey);
			ar & BOOST_SERIALIZATION_NVP(m_leftKey);
			ar & BOOST_SERIALIZATION_NVP(m_rightKey);
			ar & BOOST_SERIALIZATION_NVP(m_pauseKey);
			ar & BOOST_SERIALIZATION_NVP(m_bombKey);
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