#ifndef STATES_MAINMENUSTATE_H
#define STATES_MAINMENUSTATE_H

#include <memory>
#include "state.h"
#include "ressourcesmanager.h"
#include "uifactory.h"

namespace States {

	class MainMenu : public States::State {
	private:
		std::shared_ptr<Ressources::Manager> m_ressources;
		sf::Sprite m_logoSprite;
		Labelptr m_profileLabel;
	public:
		MainMenu(GameWindow& gameWindow, std::shared_ptr<Ressources::Manager> ressources);

		/* Virtual override */
		void draw(sf::RenderTexture& renderTexture); //Draw all the main menu options(labels)
		void handleEvents(sf::Event& event); //Handle mouse and keyboard events
		void start(); //reset focus
		void update(float delta); //Nothing
	};

}

#endif