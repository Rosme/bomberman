#include <algorithm>
#include <boost/bind.hpp>
#include "profilestate.h"
#include "gamewindow.h"
#include "utils.h"

namespace States {

	ProfileState::ProfileState(GameWindow& gameWindow, Options::Loader& profileLoader)
		: States::State(gameWindow), m_profileLoader(profileLoader), m_state(ProfileState::None), m_currentPage(0) {
			/* General State */
			addUIObjects(UIFactory::makeLabel("Profile", "important", 50, 10, sf::Color::White, 50));

			Labelptr backLabel = UIFactory::makeLabel("Back to main menu", "normal", 20, 770, sf::Color::Black, 20);
			backLabel->setFocusColor(sf::Color::White);
			backLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::State::changeGameState, boost::ref(*this), States::Menu));
			addUIObjects(backLabel);

			Labelptr newProfileLabel = UIFactory::makeLabel("New Profile", "normal", 700, 750, sf::Color::Black);
			newProfileLabel->setFocusColor(sf::Color::White);
			newProfileLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&ProfileState::setSubstate, boost::ref(*this), ProfileState::New));
			addUIObjects(newProfileLabel);

			Labelptr nextLabel = UIFactory::makeLabel("Next", "normal", 700, 600, sf::Color::Black, 20);
			nextLabel->setFocusColor(sf::Color::White);
			nextLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::ProfileState::loadNextPage, boost::ref(*this)));
			addUIObjects(nextLabel);

			Labelptr previousLabel = UIFactory::makeLabel("Previous", "normal", 50, 600, sf::Color::Black, 20);
			previousLabel->setFocusColor(sf::Color::White);
			previousLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::ProfileState::loadPreviousPage, boost::ref(*this)));
			addUIObjects(previousLabel);

			/* New Profile Substate */
			m_newProfileUIObjects.push_back(UIFactory::makeLabel("New Profile Name", "normal", 10, 5, sf::Color::White));
			m_newProfileEdit = UIFactory::makeEditText("normal", 50, 50, sf::Color::White, 20);
			m_newProfileEdit->setFocusColor(sf::Color::Black);
			m_newProfileEdit->connect(sf::Event::MouseButtonPressed, boost::bind(&UI::EditText::setFullFocus, m_newProfileEdit, true));
			m_newProfileEdit->setFullFocus(true);
			m_newProfileEdit->setInputLimit(15);
			m_newProfileEdit->setKeyFilter(UI::EditText::AlphaNum);
			m_newProfileUIObjects.push_back(m_newProfileEdit);

			m_newProfileTexture.create(300, 150);

			/* Load/Delete Profile Substate */
			m_focusedProfileUiObjects.push_back(UIFactory::makeLabel("Take a decision!", "normal", 10, 5, sf::Color::White));
			Labelptr loadLabel = UIFactory::makeLabel("Load", "normal", 50, 50, sf::Color::Black, 25);
			loadLabel->setFocusColor(sf::Color::White);
			loadLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::ProfileState::loadProfileFromLabel, boost::ref(*this)));
			m_focusedProfileUiObjects.push_back(loadLabel);

			Labelptr deleteLabel = UIFactory::makeLabel("Delete", "normal", 150, 50, sf::Color::Black, 25);
			deleteLabel->setFocusColor(sf::Color::White);
			deleteLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::ProfileState::deleteProfileFromLabel, boost::ref(*this)));
			m_focusedProfileUiObjects.push_back(deleteLabel);

			m_focusedProfileTexture.create(250, 200);
	}

	void ProfileState::update(float delta) {

	}

	void ProfileState::handleEvents(sf::Event& event) {
		if(m_state == ProfileState::None) {
			handleNormalStateEvents(event);
		} else if(m_state == ProfileState::New) {
			handleNewStateEvents(event);
		} else if(m_state == ProfileState::Focused) {
			handleFocusedStateEvents(event);
		}
	}

	void ProfileState::start() {
		resetFocus();
		setSubstate(ProfileState::None);
		m_currentPage = 0;
		loadProfilesLabel();
		m_newProfileEdit->resetText();
	}

	void ProfileState::draw(sf::RenderTexture& renderTexture) {
		States::State::draw(renderTexture);
		for(auto it = m_labelProfileList.begin(), end = m_labelProfileList.end(); it != end; ++it) {
			(*it)->draw(renderTexture);
		}
		if(m_state == ProfileState::New) {
			m_newProfileTexture.clear(sf::Color(0, 119, 170));
			for(auto it = m_newProfileUIObjects.begin(), end = m_newProfileUIObjects.end(); it != end; ++it) {
				(*it)->draw(m_newProfileTexture);
			}
			m_newProfileTexture.display();
			m_offSprite.setTexture(m_newProfileTexture.getTexture());
			m_offSprite.setPosition((m_gameWindow.WIDTH/2)-(m_offSprite.getGlobalBounds().width/2), (m_gameWindow.HEIGHT/2)-(m_offSprite.getGlobalBounds().height/2));
			renderTexture.draw(m_offSprite);
		} else if(m_state == ProfileState::Focused) {
			m_focusedProfileTexture.clear(sf::Color(0, 119, 170));
			for(auto it = m_focusedProfileUiObjects.begin(), end = m_focusedProfileUiObjects.end(); it != end; ++it) {
				(*it)->draw(m_focusedProfileTexture);
			}
			m_focusedProfileTexture.display();
			m_offSprite.setTexture(m_focusedProfileTexture.getTexture());
			m_offSprite.setPosition((m_gameWindow.WIDTH/2)-(m_offSprite.getGlobalBounds().width/2), (m_gameWindow.HEIGHT/2)-(m_offSprite.getGlobalBounds().height/2));
			renderTexture.draw(m_offSprite);
		}
	}

	void ProfileState::setSubstate(ProfileState::SubState newState) {
		m_state = newState;
	}

	void ProfileState::loadProfilesLabel() {
		m_labelProfileList.erase(m_labelProfileList.begin(), m_labelProfileList.end());

		std::vector<std::string> profileNameList = m_profileLoader.getProfilesName();
		unsigned int max;
		if(getMaximumPage() == 0 || m_currentPage == getMaximumPage()) {
			max = profileNameList.size();
		} else {
			max = (m_currentPage*5)+5;
		}

		for(unsigned int i = m_currentPage*5, j = 0; i < max; ++i) {
			Labelptr pName = UIFactory::makeLabel(Utils::formatText(profileNameList[i]), "normal", static_cast<float>((m_gameWindow.WIDTH/2)-75), static_cast<float>((j+1)*100), sf::Color::White);
			pName->setFocusColor(sf::Color::Black);
			pName->connect(sf::Event::MouseButtonPressed, boost::bind(&States::ProfileState::loadFocusedSubstate, boost::ref(*this), pName->getText()));
			m_labelProfileList.push_back(pName);
			++j;
		}
	}

	void ProfileState::loadNextPage() {
		if(m_currentPage == getMaximumPage()) {
			m_currentPage = 0;
		} else {
			++m_currentPage;
		}

		loadProfilesLabel();
	}

	void ProfileState::loadPreviousPage() {
		if(m_currentPage == 0) {
			m_currentPage = getMaximumPage();
		} else {
			--m_currentPage;
		}
		loadProfilesLabel();
	}

	unsigned int ProfileState::getMaximumPage() {
		unsigned int maxPage = 0;
		if(m_profileLoader.getProfilesName().size()%5 != 0) {
			maxPage = (m_profileLoader.getProfilesName().size()/5)+1;
		} else {
			maxPage = m_profileLoader.getProfilesName().size()/5;
		}
		
		return maxPage-1;
	}

	void ProfileState::loadFocusedSubstate(const std::string name) {
		m_focusedProfileName = name;
		setSubstate(ProfileState::Focused);
	}

	void ProfileState::loadProfileFromLabel() {
		m_profileLoader.setCurrentProfile(m_focusedProfileName);
		changeGameState(States::Menu);
	}

	void ProfileState::deleteProfileFromLabel() {
		m_profileLoader.deleteProfile(m_focusedProfileName);
		start();
	}

	void ProfileState::handleNewStateEvents(sf::Event& event) {
		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Escape) {
				setSubstate(ProfileState::None);
			} else if(event.key.code == sf::Keyboard::Return) {
				/* Create New profile and load it */
				std::string name = m_newProfileEdit->getText();
				name.erase(std::remove_if(name.begin(), name.end(), ::isspace));
				if(name.empty() || name == "...") {
					m_newProfileEdit->setFullFocus(true);
					m_newProfileEdit->resetText();
				} else {
					m_profileLoader.createProfile(Options::Profile(name));
					changeGameState(States::Menu);
				}
			} else {
				m_newProfileEdit->emit(event);
			}
		} else if(event.type == sf::Event::MouseButtonPressed) {
			sf::FloatRect bounds = m_newProfileEdit->getBoundings();
			bounds.left += m_offSprite.getPosition().x;
			bounds.top += m_offSprite.getPosition().y;
			if(bounds.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
				m_newProfileEdit->emit(event);
			}
		}
	}

	void ProfileState::handleFocusedStateEvents(sf::Event& event) {
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			setSubstate(ProfileState::None);
		}

		if(event.type == sf::Event::MouseMoved) {
			for(auto it = m_focusedProfileUiObjects.begin(), end = m_focusedProfileUiObjects.end(); it != end; ++it) {
				sf::FloatRect bounds = (*it)->getBoundings();
				bounds.left += m_offSprite.getPosition().x;
				bounds.top += m_offSprite.getPosition().y;
				if(bounds.contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y))) {
					(*it)->setFocus(true);
				} else {
					(*it)->setFocus(false);
				}
			}
		}

		if(event.type == sf::Event::MouseButtonPressed) {
			for(auto it = m_focusedProfileUiObjects.begin(), end = m_focusedProfileUiObjects.end(); it != end; ++it) {
				sf::FloatRect bounds = (*it)->getBoundings();
				bounds.left += m_offSprite.getPosition().x;
				bounds.top += m_offSprite.getPosition().y;
				if(bounds.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
					(*it)->emit(event);
				}
			}
		}
	}

	void ProfileState::handleNormalStateEvents(sf::Event& event) {
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

			for(auto it = m_labelProfileList.begin(), end = m_labelProfileList.end(); it != end; ++it) {
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

			for(auto it = m_labelProfileList.begin(), end = m_labelProfileList.end(); it != end; ++it) {
				sf::FloatRect bounds = (*it)->getBoundings();
				if(bounds.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
					(*it)->emit(event);
				}
			}
		}
	}
}