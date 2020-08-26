#ifndef STATES_OPTIONSTATE_H
#define STATES_OPTIONSTATE_H

#include "state.h"
#include "uifactory.h"
#include "profileloader.h"

namespace States {

	class OptionState : public States::State {
	private:
		Options::Loader& m_profileLoader;
		Labelptr m_musicLabel,
				 m_soundLabel;
		EditTextptr m_upEdit,
					m_downEdit,
					m_leftEdit,
					m_rightEdit,
					m_pauseEdit,
					m_bombEdit;

		void lowerMusic(); //Less music
		void lowerSound(); //Less sound
		void raiseMusic(); //More music
		void raiseSound(); //More sound
	public:
		/* Ctor */
		OptionState(GameWindow& gameWindow, Options::Loader& profileLoader);

		/* Virtual Override */
		void changeGameState(const States::GameState newState); //Save the options to profile, and change game state
		void handleEvents(sf::Event& event); //Handle mouse and keyboard events
		void start(); //reset focus, load options info
		void update(float delta); //nothing
	};

}

#endif