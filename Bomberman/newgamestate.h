#ifndef STATES_NEWGAMESTATE_H
#define STATES_NEWGAMESTATE_H

#include <list>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/discrete_distribution.hpp>
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
		UIObjects m_mapListLabel;
		Stateptr m_subState;
		bool m_playing;

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

		boost::mt19937 m_gen;
		std::list<Ressources::FirePtr> m_fires;
		DataModel::MapLoader& m_mapLoader;
		DataModel::Map m_map;
		sf::RenderTexture m_mapTexture,
						  m_headerTexture,
						  m_pausedTexture;
		sf::Sprite m_mapSprite,
				   m_headerSprite,
				   m_playerBombSprite,
				   m_playerFireSprite,
				   m_pausedSprite;
		std::vector<sf::Sprite> m_headerSprites;
		std::vector<Labelptr> m_playersLife,
							  m_pausedLabel;
		Labelptr m_playerBombLvl,
				 m_playerFireLvl,
				 m_playerScore;
		unsigned int m_currentPlayerScore;
		bool m_firstGame,
			 m_paused;

		sf::RectangleShape m_seperator;
		NewGameState* m_parent;

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