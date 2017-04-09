#ifndef STATES_MAINMENUSTATE_H
#define STATES_MAINMENUSTATE_H

#include "state.h"
#include "ressourcesmanager.h"
#include "uifactory.h"

namespace States {

	class MainMenu : public States::State {
	private:
		boost::shared_ptr<Ressources::Manager> m_ressources;
		sf::Sprite m_logoSprite;
		Labelptr m_profileLabel;
	public:
		MainMenu(GameWindow& gameWindow, boost::shared_ptr<Ressources::Manager> ressources);

		/* Virtual override */
		void draw(sf::RenderTexture& renderTexture); //Draw all the main menu options(labels)
		void handleEvents(sf::Event& event); //Handle mouse and keyboard events
		void start(); //reset focus
		void update(float delta); //Nothing
	};

}

#endif