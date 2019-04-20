#ifndef STATES_PROFILESTATE_H
#define STATES_PROFILESTATE_H

#include "state.h"
#include "uifactory.h"
#include "profileloader.h"

namespace States {

	class ProfileState : public States::State {
	private:
		enum SubState {
			None,
			New,
			Focused
		};
		Options::Loader& m_profileLoader;
		ProfileState::SubState m_state;
		unsigned int m_currentPage;
		sf::RenderTexture m_newProfileTexture;
		sf::RenderTexture m_focusedProfileTexture;
		EditTextptr m_newProfileEdit;
		States::UIObjects m_newProfileUIObjects;
		States::UIObjects m_focusedProfileUiObjects;
		States::UIObjects m_labelProfileList;
		std::string m_focusedProfileName;
		sf::Sprite m_offSprite;

		void deleteProfileFromLabel(); //Delete the profile
		unsigned int getMaximumPage(); //Returns the amount of profile page there is
		void handleFocusedStateEvents(sf::Event& event); //Handle events when a profile is focused(load-delete)
		void handleNewStateEvents(sf::Event& event); //Handle events when creating a new profile
		void handleNormalStateEvents(sf::Event& event); //Handle events when all is normal
		void loadFocusedSubstate(const std::string name); //Change the substate to the focus(load-delete)
		void loadNextPage(); //Change player's list page
		void loadPreviousPage(); //Change player's list page
		void loadProfileFromLabel(); //Load the profile
		void loadProfilesLabel(); //Load the list of all profile
		void setSubstate(ProfileState::SubState newState); //Change substate
	public:
		/* Ctor */
		ProfileState(GameWindow& gameWindow, Options::Loader& profileLoader);

		/* Virtual Override */
		void draw(sf::RenderTexture& renderTexture); //Draw all the profiles and sub menus
		void handleEvents(sf::Event& event); //Handle mouse and keyboard events
		void start(); //reset focus, load profile list
		void update(float delta); //nothing
	};

}

#endif