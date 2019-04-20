#ifndef STATES_EDITORSTATE_H
#define STATES_EDITORSTATE_H

#include <boost/smart_ptr.hpp>
#include "state.h"
#include "uifactory.h"
#include "ressourcesmanager.h"
#include "map.h"
#include "maploader.h"

namespace States {

	class EditorState : public States::State {
	private:
		enum Substate {
			None,
			Save,
			Load
		};
		sf::RectangleShape m_seperator;
		DataModel::Map m_map;
		boost::shared_ptr<Ressources::Manager> m_ressources;
		DataModel::Tile::Type m_currentTile;
		DataModel::MapLoader& m_mapLoader;
		Substate m_currentSubstate;

		sf::RenderTexture m_mapTexture;
		sf::RenderTexture m_headerTexture;
		sf::RenderTexture m_newMapTexture;
		sf::RenderTexture m_loadMapTexture;
		
		sf::Sprite m_mapSprite;
		sf::Sprite m_headerSprite;
		sf::Sprite m_newMapSprite;
		sf::Sprite m_loadMapSprite;

		States::UIObjects m_newMapObjects;
		States::UIObjects m_loadMapObjects;
		EditTextptr m_mapNameEdit;
		
		
		bool m_mouseDownOnMap;
		
		std::vector<sf::Sprite> m_playersSprite;
		std::vector<sf::Sprite> m_tileSprite;
		std::pair<bool, int> m_playerChose;

		void changeCurrentTileType(DataModel::Tile::Type type); //Change the selected tile to put on map
		void handleLoadSubstateEvents(sf::Event& event); //Events when loading
		void handleNoneSubstateEvents(sf::Event& event); //Events in normal state(Editing)
		void handleSaveSubstateEvents(sf::Event& event); //Events when saving
		void loadMap(const std::string& name); //Load the map
		void loadMapList(); //List all the map
		void saveMap(const std::string& name); //Save the map
		void setCurrentSubstate(Substate substate); //Change the substate
		void setTileToMap(sf::Vector2i position); //Put the tile on the map
		sf::Vector2i toMapPosition(sf::Vector2f mousePosition); //Convert from mouse position to the map position(float in the game window -> int in the tile map)

	public:
		/* Ctor */
		EditorState(GameWindow& gameWindow, boost::shared_ptr<Ressources::Manager> ressources, DataModel::MapLoader& mapLoader);

		/* Virtual override */
		void draw(sf::RenderTexture& texture); //Draw the header, map, and everything
		void handleEvents(sf::Event& event); //Handle the events, will send to sub version
		void start(); //Execute on start of state, clear, load map, reset map
		void update(float delta); //Nothing
	};

}

#endif