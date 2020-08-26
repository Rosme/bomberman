#ifndef RESSOURCES_MANAGER_H
#define RESSOURCES_MANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace Ressources {

	class Graphic : sf::NonCopyable {
		friend class Manager;
		typedef std::map<std::string, sf::Font> Fonts;
		typedef std::map<std::string, sf::Texture> Textures;
	private:
		Fonts m_fontsMap;
		Textures m_texturesMap;

		Graphic(const std::string& fontPath, const std::string& texturePath);
		sf::Font& getFont(const std::string& fontName); //Returns a specific font
		sf::Texture& getTexture(const std::string& textureName); //Returns a specific texture
	};

	class Manager {
	private:
		Ressources::Graphic m_graphicRessources;
	public:
		Manager();

		sf::Font& getFont(const std::string& fontName); //Returns a specific font
		sf::Texture& getTexture(const std::string& textureName); //Returns a specific texture
	};

}

#endif