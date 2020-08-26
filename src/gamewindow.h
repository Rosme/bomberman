#ifndef WINDOW_GAMEWINDOW_H
#define WINDOW_GAMEWINDOW_H

#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "state.h"
#include "ressourcesmanager.h"
#include "profileloader.h"
#include "maploader.h"
#include "scoreloader.h"

typedef std::shared_ptr<States::State> Stateptr;

class GameWindow : sf::NonCopyable {
private:
	typedef std::unordered_map<States::GameState, std::shared_ptr<States::State>> GameStates;

	sf::RenderWindow& m_renderWindow;
	States::GameState m_currentStateCode;
	Stateptr m_currentState;
	std::shared_ptr<Ressources::Manager> m_ressources;
	Options::Loader m_profileLoader;
	DataModel::MapLoader m_mapLoader;
	DataModel::ScoreLoader m_scoreLoader;

public:
	const unsigned int WIDTH;
	const unsigned int HEIGHT;

private:
	sf::RenderTexture m_renderTexture;
	sf::Sprite m_renderSprite;
	sf::RectangleShape m_screenClearer;
	GameStates m_gameStates;

	/* Methods */
	void loadFirstGame(); //Load the first game state for first time
	void loadGameStates(); //Load all the game state
public:
	/* Ctor */
	GameWindow(sf::RenderWindow& renderWindow);

	/* Methods */
	void changeState(const States::GameState newState); //Change the game state
	void close(); //Close the game, and window
	void draw(); //Draw the window
	Options::Profile& getCurrentProfile(); //Return the current profile
	std::shared_ptr<Ressources::Manager> getRessourcesManager(); //Return the ressources manager
	DataModel::ScoreLoader& getScoreLoader(); //Return the score loader
	void handleEvents(sf::Event& event); //Handle events, passed to state
	void setCurrentProfile(Options::Profile& profile); //Set the current playing profile
	void update(); //Call state update
};

#endif