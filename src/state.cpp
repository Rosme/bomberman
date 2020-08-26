#include "state.h"
#include "gamewindow.h"

namespace States {

	State::State(GameWindow& gameWindow)
		: m_gameWindow(gameWindow) {}

	State::~State() {}

	void State::draw(sf::RenderTexture& renderTexture) {
		for(auto it = m_uiObjects.begin(), end = m_uiObjects.end(); it != end; ++it) {
			(*it)->draw(renderTexture);
		}
	}

	void State::addUIObjects(UIObjectPtr object) {
		m_uiObjects.push_back(object);
	}

	void State::changeGameState(const States::GameState newState) {
		m_gameWindow.changeState(newState);
	}

	void State::resetFocus() {
		for(auto it = m_uiObjects.begin(), end = m_uiObjects.end(); it != end; ++it) {
			(*it)->setFocus(false);
		}
	}
}