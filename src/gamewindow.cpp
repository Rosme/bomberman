#include "gamewindow.h"

#include "mainmenustate.h"
#include "optionstate.h"
#include "firstgamestate.h"
#include "profilestate.h"
#include "editorstate.h"
#include "newgamestate.h"
#include "scorestate.h"
#include "uifactory.h"

GameWindow::GameWindow(sf::RenderWindow& renderWindow)
	: m_renderWindow(renderWindow), 
	m_currentStateCode(States::Menu), 
	m_currentState(nullptr), 
	m_ressources(new Ressources::Manager()),
	m_profileLoader("profile/"),
	m_mapLoader("map/"),
	m_scoreLoader("profile/playersScore"),
	WIDTH(renderWindow.getSize().x),
	HEIGHT(renderWindow.getSize().y) {

	m_screenClearer.setSize(sf::Vector2f(static_cast<float>(WIDTH), static_cast<float>(HEIGHT)));
	m_screenClearer.setPosition(0.f, 0.f);
	m_screenClearer.setFillColor(sf::Color::Transparent);

	UIFactory::registerRessourceManager(m_ressources);
	if(!m_renderTexture.create(renderWindow.getSize().x, renderWindow.getSize().y)) {
		throw std::runtime_error("Couldn't create the rendering texture for the game");
	}
	m_renderSprite.setTexture(m_renderTexture.getTexture());
	/**
	Creating states and setting the current state
	**/
	if(m_profileLoader.isFirstGame()) {
		loadFirstGame();
	} else {
		loadGameStates();
	}
}

void GameWindow::draw() {
	m_renderTexture.clear(sf::Color(0, 162, 232));
	m_currentState->draw(m_renderTexture);
	m_renderTexture.draw(m_screenClearer);
	m_renderTexture.display();

	m_renderWindow.clear();
	m_renderWindow.draw(m_renderSprite);
	m_renderWindow.display();
}

void GameWindow::handleEvents(sf::Event& event) {
	if(event.type == sf::Event::Closed) {
		m_renderWindow.close();
	}
	m_currentState->handleEvents(event);
}

void GameWindow::update() {
	m_currentState->update(1.0);
}

void GameWindow::changeState(const States::GameState newState) {
	if(newState == States::FirstTimeReady) {
		loadGameStates();
	} else {
		m_currentStateCode = newState;
		m_currentState = m_gameStates[newState];
		m_currentState->start();
	}
}

void GameWindow::close() {
	m_renderWindow.close();
}

Options::Profile& GameWindow::getCurrentProfile() {
	return m_profileLoader.getCurrentProfile();
}

void GameWindow::setCurrentProfile(Options::Profile& profile) {
	m_profileLoader.setCurrentProfile(profile.getName());
}

void GameWindow::loadFirstGame() {
	std::shared_ptr<States::State> firstGameState(new States::FirstGameState(*this, m_profileLoader));
	m_gameStates[States::FirstTime] = firstGameState;
	changeState(States::FirstTime);
}

void GameWindow::loadGameStates() {
	Stateptr mainMenuState(new States::MainMenu(*this, m_ressources));
	m_gameStates[States::Menu] = mainMenuState;
	
	Stateptr optionState(new States::OptionState(*this, m_profileLoader));
	m_gameStates[States::Options] = optionState;

	Stateptr profile(new States::ProfileState(*this, m_profileLoader));
	m_gameStates[States::Profile] = profile;

	Stateptr editor(new States::EditorState(*this, m_ressources, m_mapLoader));
	m_gameStates[States::Editor] = editor;

	Stateptr game(new States::NewGameState(*this, m_mapLoader));
	m_gameStates[States::Game] = game;

	Stateptr score(new States::ScoreState(*this, m_scoreLoader));
	m_gameStates[States::Score] = score;

	changeState(States::Menu);
}

std::shared_ptr<Ressources::Manager> GameWindow::getRessourcesManager() {
	return m_ressources;
}

DataModel::ScoreLoader& GameWindow::getScoreLoader() {
	return m_scoreLoader;
}