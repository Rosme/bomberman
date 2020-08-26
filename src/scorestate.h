#ifndef STATES_SCORESTATE_H
#define STATES_SCORESTATE_H

#include "state.h"
#include "scoreloader.h"

namespace States {

	class ScoreState : public States::State {
	private:
		DataModel::ScoreLoader& m_scoreLoader;
		UIObjects m_scoreLabels;

	public:
		ScoreState(GameWindow& gameWindow, DataModel::ScoreLoader& scoreLoader);

		void draw(sf::RenderTexture& renderTexture); //Draw all the scores
		void start(); //reset focus, load the high scores
		void handleEvents(sf::Event& event); //Handle mouse and keyboard events
		void update(float delta); //Nothing
	};

}

#endif