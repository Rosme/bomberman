#ifndef STATES_NEWGAMESTATE_H
#define STATES_NEWGAMESTATE_H

#include <list>
#include <random>
#include "state.h"
#include "maploader.h"
#include "map.h"
#include "gamewindow.h"
#include "fire.h"
#include "bomb.h"
#include "powerup.h"
#include "uifactory.h"

namespace States {

	class PlayingState;

	class NewGameState : public States::State {
	private:
		DataModel::MapLoader& m_mapLoader;
		Stateptr m_subState;
		bool m_playing;
		UIObjects m_mapListLabel;
		std::random_device m_device;
		std::mt19937 m_gen;

		void startPlaying(const std::string& mapName); //Start the game, and set substate to playing state
	public:
		NewGameState(GameWindow& gameWindow, DataModel::MapLoader& mapLoader);

		void draw(sf::RenderTexture& renderTexture); //Draw the list of map available to play
		void handleEvents(sf::Event& event); //Handle mouse and keyboard events
		void loadRandomMap(); //Load a random map, and goes to startPlaying
		void start(); //reset focus
		void stopPlaying(); //Stop the game
		void update(float delta); //Nothing
	};

	class PlayingState : public States::State {
	private:
		typedef std::vector<DataModel::Player*>::iterator PlayerIterator;

		DataModel::MapLoader& m_mapLoader;
		DataModel::Map m_map;
		NewGameState* m_parent;
		std::random_device m_device;
		std::mt19937 m_gen;
		sf::RectangleShape m_seperator;
		unsigned int m_currentPlayerScore;
		bool m_firstGame;
		bool m_paused;

		std::list<Ressources::FirePtr> m_fires;
		
		
		sf::RenderTexture m_mapTexture;
		sf::RenderTexture m_headerTexture;
		sf::RenderTexture m_pausedTexture;
		sf::Sprite m_mapSprite;
		sf::Sprite m_headerSprite;
		sf::Sprite m_playerBombSprite;
		sf::Sprite m_playerFireSprite;
		sf::Sprite m_pausedSprite;
		std::vector<sf::Sprite> m_headerSprites;
		std::vector<Labelptr> m_playersLife,
							  m_pausedLabel;
		Labelptr m_playerBombLvl,
				 m_playerFireLvl,
				 m_playerScore;
	
		void pauseGame(); //Pause the game, or re-start it
		void verifyPlayerFireCollision(PlayerIterator begin, PlayerIterator end, sf::Vector2i position, unsigned int owner); //Fire + player = OUCH and Score
	public:
		static const unsigned int DESTRUCTION_SCORE,
								  PLAYER_SCORE,
								  POWERUP_SCORE;
		PlayingState(GameWindow& gameWindow, DataModel::MapLoader& mapLoader, States::NewGameState* parent);

		void draw(sf::RenderTexture& renderTexture); //Draws The header, the pause menu, and the map, with players, and all
		void handleEvents(sf::Event& event); //Handle keyboard related events
		void raiseScore(unsigned int amount); //Raise the score of the player
		void setMap(const std::string& mapName); //Set the map to play
		void start(); //reset focus, clear map, reset power level, reset bomb quantity, reset score
		void update(float delta); //Manage all player, movement, collision, explosion
		void verifyExplosionCollision(int level, sf::Vector2i startPosition, int owner); //Verify if a bomb explosion touch something
	};

}

#endif