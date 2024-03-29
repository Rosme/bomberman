#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

#include <string>
#include <SFML/Window.hpp>

#define UNUSED(x) (void)(x)

namespace Utils {

	/**
	 * returns the string value of a key
	 **/
	std::string getKeyName(const sf::Keyboard::Key key);

	/**
	 * returns the sf::keyboard::key of a string
	 **/
	sf::Keyboard::Key getKeyValue(const std::string& key);

	/**
	 * returns the amount of frame in a second calculated by the clock
	 **/
	float getFps(const sf::Time& time);

	/**
	 * Converts a value of any type to string
	 **/
	template<class T>
	std::string toString(T t) {
		return std::to_string(t);
	}

	/**
	 * Format a string of text for the first letter to be capital, and others in lower case
	 **/
	std::string formatText(std::string text);
}

#endif
