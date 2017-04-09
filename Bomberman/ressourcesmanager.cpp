#include "ressourcesmanager.h"
#include <boost/filesystem.hpp>

namespace Ressources {

	/** Graphic Class **/
	Graphic::Graphic(const std::string& fontPath, const std::string& texturePath) {
		namespace bfs = boost::filesystem;
		bfs::path fPath(fontPath), tPath(texturePath);

		//Making sure directory does exist and is valid
		if(bfs::exists(fontPath) && bfs::exists(texturePath) &&
		   bfs::is_directory(fontPath) && bfs::is_directory(texturePath)) {
				/* Loading files within the map. Every texture name as the key */
				for(auto it = bfs::directory_iterator(fPath), end = bfs::directory_iterator(); it != end; ++it) {
					m_fontsMap[(*it).path().stem().string()].loadFromFile((*it).path().string());
				}

				for(auto it = bfs::directory_iterator(tPath), end = bfs::directory_iterator(); it != end; ++it) {
					m_texturesMap[(*it).path().stem().string()].loadFromFile((*it).path().string());
					sf::Image& img = m_texturesMap[(*it).path().stem().string()].copyToImage();
					img.createMaskFromColor(sf::Color(255,0 ,255));
					m_texturesMap[(*it).path().stem().string()].loadFromImage(img);
				}
		} else {
			throw std::runtime_error("Directory texture/font file does not exist or is not valid");
		}
	}

	/** Manager Class **/
	Manager::Manager() 
		: m_graphicRessources("assets/fonts/", "assets/texture/") { }

	sf::Font& Manager::getFont(const std::string& fontName) {
		auto font = m_graphicRessources.m_fontsMap.find(fontName);
		if(font == m_graphicRessources.m_fontsMap.end()) {
			throw std::runtime_error("Request to get an unloaded font: " + fontName);
		}
		return font->second;
	}

	sf::Texture& Manager::getTexture(const std::string& textureName) {
		auto texture = m_graphicRessources.m_texturesMap.find(textureName);
		if(texture == m_graphicRessources.m_texturesMap.end()) {
			throw std::runtime_error("Request to get an unloaded texture: " + textureName);
		}
		return texture->second;
	}

}