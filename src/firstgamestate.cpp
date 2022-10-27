
#include "firstgamestate.h"
#include "gamewindow.h"
#include "utils.h"

namespace States {

	FirstGameState::FirstGameState(GameWindow& gameWindow, Options::Loader& profileLoader)
		: States::State(gameWindow), m_profileLoader(profileLoader) {
		
		addUIObjects(UIFactory::makeLabel("You have to make a player profile!", "important", 200, 300, sf::Color::White, 30));
		addUIObjects(UIFactory::makeLabel("There isn't any player yet!", "important", 275, 340, sf::Color::White, 20));

		m_profileName = UIFactory::makeEditText("normal", 350, 400, sf::Color::White, 20);
		m_profileName->setFocusColor(sf::Color::Black);
		m_profileName->connect(sf::Event::MouseButtonPressed, [this]() { m_profileName->setFullFocus(true); });
		m_profileName->setFullFocus(true);
		m_profileName->setKeyFilter(UI::EditText::AlphaNum);
		addUIObjects(m_profileName);

		Buttonptr continueButton = UIFactory::makeButton("Create!", "button", 600, 600, sf::Color::White, sf::Color::Black, sf::Color::White);
		continueButton->connect(sf::Event::MouseButtonPressed, [this]() { changeGameState(States::FirstTimeReady); });
		addUIObjects(continueButton);
	}

	void FirstGameState::update(float delta) {
        UNUSED(delta);
    }

	void FirstGameState::handleEvents(sf::Event& event) {
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

		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Return) {
				changeGameState(States::FirstTimeReady);
			} else {
				for(auto it = m_uiObjects.begin(), end = m_uiObjects.end(); it != end; ++it) {
					(*it)->emit(event);
				}
			}
		}
	}

	void FirstGameState::changeGameState(const States::GameState newState) {
		Options::Profile profile(m_profileName->getText());
		m_profileLoader.createProfile(profile);
		States::State::changeGameState(newState);
	}

	void FirstGameState::start() {
		resetFocus();
	}
}
