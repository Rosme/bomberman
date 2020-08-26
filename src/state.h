#ifndef STATES_STATE_H
#define STATES_STATE_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "uiobject.h"

class GameWindow;

namespace States {
	enum GameState {
		Game,
		Profile,
		Options,
		Menu,
		Editor,
		Score,
		FirstTime,
		FirstTimeReady
	};

	typedef std::shared_ptr<UI::Object> UIObjectPtr;
	typedef std::vector<UIObjectPtr> UIObjects;

	class State {
	protected:
		GameWindow& m_gameWindow;
		UIObjects m_uiObjects;
	public:
		/* Ctor */
		State(GameWindow& gameWindow);
		/* Virtual Dtor*/
		virtual ~State();

		/* Pure virtual methods */
		virtual void update(float delta) = 0;
		virtual void handleEvents(sf::Event& event) = 0;
		virtual void start() = 0;

		/* Virtual methods, inheritance and override */
		virtual void draw(sf::RenderTexture& renderTexture);
		virtual void changeGameState(const States::GameState newState);

		/* Methods */
		void addUIObjects(UIObjectPtr object);
		void resetFocus();
	};

}

#endif