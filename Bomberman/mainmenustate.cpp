#include <boost/bind.hpp>
#include "mainmenustate.h"
#include "gamewindow.h"
#include "utils.h"

namespace States {

	MainMenu::MainMenu(GameWindow& gameWindow, boost::shared_ptr<Ressources::Manager> ressources)
		: States::State(gameWindow), m_ressources(ressources), m_logoSprite(ressources->getTexture("logo")) {
			m_logoSprite.setPosition((gameWindow.WIDTH/2)-(m_logoSprite.getGlobalBounds().width/2), 50);
			Labelptr gameLabel = UIFactory::makeLabel("New Game", "normal", 375, 175, sf::Color::Black);
			gameLabel->setFocusColor(sf::Color::White);
			gameLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::State::changeGameState, boost::ref(*this), States::Game));
			States::State::addUIObjects(gameLabel);

			Labelptr editorLabel = UIFactory::makeLabel("Editor", "normal", 375, 275, sf::Color::Black);
			editorLabel->setFocusColor(sf::Color::White);
			editorLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::State::changeGameState, boost::ref(*this), States::Editor));
			addUIObjects(editorLabel);

			Labelptr scoreLabel = UIFactory::makeLabel("HighScores", "normal", 375, 375, sf::Color::Black);
			scoreLabel->setFocusColor(sf::Color::White);
			scoreLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::State::changeGameState, boost::ref(*this), States::Score));
			addUIObjects(scoreLabel);
			
			Labelptr optionLabel = UIFactory::makeLabel("Options", "normal", 375, 475, sf::Color::Black);
			optionLabel->setFocusColor(sf::Color::White);
			optionLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::State::changeGameState, boost::ref(*this), States::Options));
			addUIObjects(optionLabel);

			Labelptr quitLabel = UIFactory::makeLabel("Quit", "normal", 375, 575, sf::Color::Black);
			quitLabel->setFocusColor(sf::Color::White);
			quitLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&GameWindow::close, boost::ref(gameWindow)));
			addUIObjects(quitLabel);

			m_profileLabel = UIFactory::makeLabel("Hey", "normal", 10, static_cast<float>(gameWindow.HEIGHT-30), sf::Color::Black, 15);
			m_profileLabel->setFocusColor(sf::Color::White);
			m_profileLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::State::changeGameState, boost::ref(*this), States::Profile));
			addUIObjects(m_profileLabel);
	}

	void MainMenu::update(float delta) {
	}

	void MainMenu::handleEvents(sf::Event& event) {
		if(event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
			case sf::Keyboard::Escape:
			case sf::Keyboard::Q:
				m_gameWindow.close();
				break;
			case sf::Keyboard::N:
				changeGameState(States::Game);
				break;
			case sf::Keyboard::E:
				changeGameState(States::Editor);
				break;	
			case sf::Keyboard::H:
				changeGameState(States::Score);
				break;
			case sf::Keyboard::O:
				changeGameState(States::Options);
				break;
			case sf::Keyboard::P:
				changeGameState(States::Profile);
				break;
			}
		}
		if(event.type == sf::Event::MouseMoved) {
			for(auto it = m_uiObjects.begin(), end = m_uiObjects.end(); it != end; ++it) {
				sf::FloatRect bounds = (*it)->getBoundings();
				if(bounds.contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y))) {
					(*it)->setFocus(true);
				} else {
					(*it)->setFocus(false);
				}
			}
		}
		if(event.type == sf::Event::MouseButtonPressed) {
			for(auto it = m_uiObjects.begin(), end = m_uiObjects.end(); it != end; ++it) {
				sf::FloatRect bounds = (*it)->getBoundings();
				if(bounds.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
					(*it)->emit(event);
				}
			}
		}
	}

	void MainMenu::draw(sf::RenderTexture& renderTexture) {
		States::State::draw(renderTexture);
		renderTexture.draw(m_logoSprite);
	}

	void MainMenu::start() {
		resetFocus();
		m_profileLabel->setText("Not " + Utils::formatText(m_gameWindow.getCurrentProfile().getName()) + "? Click here to change player!");
	}
}