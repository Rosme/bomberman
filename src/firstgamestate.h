#ifndef STATES_FIRSTGAMESTATE_H
#define STATES_FIRSTGAMESTATE_H

#include "state.h"
#include "profileloader.h"
#include "uifactory.h"

namespace States {

	class FirstGameState : public States::State {
	private:
		EditTextptr m_profileName;
		Options::Loader& m_profileLoader;

	public:
		/* Ctor */
		FirstGameState(GameWindow& gameWindow, Options::Loader& profileLoader);

		/* Virtual override */
		void changeGameState(const States::GameState newState); //Call parent changeGameState, and create the profile
		void handleEvents(sf::Event& event); //Handle events
		void start(); //Nothing
		void update(float delta); //Nothing
	};

}

#endif