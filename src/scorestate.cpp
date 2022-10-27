#include "gamewindow.h"
#include "scorestate.h"
#include "uifactory.h"
#include "utils.h"

namespace States {

	ScoreState::ScoreState(GameWindow& gameWindow, DataModel::ScoreLoader& scoreLoader)
		: State(gameWindow), m_scoreLoader(scoreLoader) {
			addUIObjects(UIFactory::makeLabel("High Score", "important", 50, 10, sf::Color::White, 50));

			Labelptr backLabel = UIFactory::makeLabel("Back to main menu", "normal", 20, 770, sf::Color::Black, 20);
			backLabel->setFocusColor(sf::Color::White);
			backLabel->connect(sf::Event::MouseButtonPressed, [this]() { changeGameState(States::Menu); });
			addUIObjects(backLabel);
		}

	void ScoreState::start() {
		States::State::resetFocus();
		m_scoreLoader.loadScores();
		DataModel::ScoreArray& scores = m_scoreLoader.getScores();
		
		m_scoreLabels.clear();

		for(std::size_t i = 0, size = scores.size(); i < size; ++i) {
			m_scoreLabels.push_back(UIFactory::makeLabel(scores[i].first + " : " + Utils::toString(scores[i].second), "normal", static_cast<float>((m_gameWindow.WIDTH/2)-75), static_cast<float>((i+1)*75), sf::Color::Black, 20));
		}
	}

	void ScoreState::update(float delta) {
        UNUSED(delta);
    }

	void ScoreState::handleEvents(sf::Event& event) {
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			changeGameState(States::Menu);
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

	void ScoreState::draw(sf::RenderTexture& renderTexture) {
		States::State::draw(renderTexture);

		for(auto it = m_scoreLabels.begin(), end = m_scoreLabels.end(); it != end; ++it) {
			(*it)->draw(renderTexture);
		}
	}
}
