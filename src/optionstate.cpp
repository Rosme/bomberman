#include "optionstate.h"
#include "gamewindow.h"
#include "utils.h"

namespace States {

	OptionState::OptionState(GameWindow& gameWindow, Options::Loader& profileLoader)
		: States::State(gameWindow), m_profileLoader(profileLoader) {
			/* Creating static label that won't change */
			addUIObjects(UIFactory::makeLabel("Options", "important", 50, 10, sf::Color::White, 50));

			addUIObjects(UIFactory::makeLabel("Music Volume", "important", 100, 100, sf::Color::White, 40));

			addUIObjects(UIFactory::makeLabel("Sound Volume", "important", 100, 175, sf::Color::White, 40));

			addUIObjects(UIFactory::makeLabel("Controls", "important", 100, 250, sf::Color::White, 40));

			addUIObjects(UIFactory::makeLabel("Move Up", "normal", 200, 325, sf::Color::White));
			addUIObjects(UIFactory::makeLabel("Move Down", "normal", 200, 390, sf::Color::White));
			addUIObjects(UIFactory::makeLabel("Move Left", "normal", 200, 455, sf::Color::White));
			addUIObjects(UIFactory::makeLabel("Move Right", "normal", 200, 520, sf::Color::White));
			addUIObjects(UIFactory::makeLabel("Pause", "normal", 200, 585, sf::Color::White));
			addUIObjects(UIFactory::makeLabel("Place bomb", "normal", 200, 650, sf::Color::White));

			Labelptr backLabel = UIFactory::makeLabel("Back to main menu", "normal", 20, 750, sf::Color::Black, 20);
			backLabel->setFocusColor(sf::Color::White);
			backLabel->connect(sf::Event::MouseButtonPressed, [this]() { changeGameState(States::Menu); });
			addUIObjects(backLabel);

			Options::Profile& currentProfile = profileLoader.getCurrentProfile();

			Labelptr lowerMusicLabel = UIFactory::makeLabel("[-]", "option-button", 550, 120, sf::Color::Black, 20);
			lowerMusicLabel->connect(sf::Event::MouseButtonPressed, [this]() { lowerMusic(); });
			lowerMusicLabel->setFocusColor(sf::Color::White);
			addUIObjects(lowerMusicLabel);

			Labelptr raiseMusicLabel = UIFactory::makeLabel("[+]", "option-button", 650, 120, sf::Color::Black, 20);
			raiseMusicLabel->connect(sf::Event::MouseButtonPressed, [this]() { raiseMusic(); });
			raiseMusicLabel->setFocusColor(sf::Color::White);
			addUIObjects(raiseMusicLabel);

			Labelptr lowerSoundLabel = UIFactory::makeLabel("[-]", "option-button", 550, 195, sf::Color::Black, 20);
			lowerSoundLabel->connect(sf::Event::MouseButtonPressed, [this]() { lowerSound(); });
			lowerSoundLabel->setFocusColor(sf::Color::White);
			addUIObjects(lowerSoundLabel);

			Labelptr raiseSoundLabel = UIFactory::makeLabel("[+]", "option-button", 650, 195, sf::Color::Black, 20);
			raiseSoundLabel->connect(sf::Event::MouseButtonPressed, [this]() { raiseSound(); });
			raiseSoundLabel->setFocusColor(sf::Color::White);
			addUIObjects(raiseSoundLabel);

			/* Creating dynamic labels */
			m_musicLabel = UIFactory::makeLabel(Utils::toString(currentProfile.getMusicLevel()), "normal", 600, 120, sf::Color::White, 20);
			addUIObjects(m_musicLabel);

			m_soundLabel = UIFactory::makeLabel(Utils::toString(currentProfile.getSoundLevel()), "normal", 600, 195, sf::Color::White, 20);
			addUIObjects(m_soundLabel);

			Options::Option& currentOptions = currentProfile.getOption();

			m_upEdit = UIFactory::makeEditText("normal", 600, 335, sf::Color::White, 20);
			m_upEdit->setFocusColor(sf::Color::Black);
			m_upEdit->setText(Utils::getKeyName(currentOptions.getKey(Options::Up)));
			m_upEdit->setInputLimit(1, true);
			m_upEdit->connect(sf::Event::MouseButtonPressed, [this]() { m_upEdit->setFullFocus(true); });
			addUIObjects(m_upEdit);

			m_downEdit = UIFactory::makeEditText("normal", 600, 400, sf::Color::White, 20);
			m_downEdit->setFocusColor(sf::Color::Black);
			m_downEdit->setText(Utils::getKeyName(currentOptions.getKey(Options::Up)));
			m_downEdit->setInputLimit(1, true);
			m_downEdit->connect(sf::Event::MouseButtonPressed, [this]() { m_downEdit->setFullFocus(true); });
			addUIObjects(m_downEdit);

			m_leftEdit = UIFactory::makeEditText("normal", 600, 465, sf::Color::White, 20);
			m_leftEdit->setFocusColor(sf::Color::Black);
			m_leftEdit->setText(Utils::getKeyName(currentOptions.getKey(Options::Up)));
			m_leftEdit->setInputLimit(1, true);
			m_leftEdit->connect(sf::Event::MouseButtonPressed, [this]() { m_leftEdit->setFullFocus(true); });
			addUIObjects(m_leftEdit);

			m_rightEdit = UIFactory::makeEditText("normal", 600, 530, sf::Color::White, 20);
			m_rightEdit->setFocusColor(sf::Color::Black);
			m_rightEdit->setText(Utils::getKeyName(currentOptions.getKey(Options::Up)));
			m_rightEdit->setInputLimit(1, true);
			m_rightEdit->connect(sf::Event::MouseButtonPressed, [this]() { m_rightEdit->setFullFocus(true); });
			addUIObjects(m_rightEdit);

			m_pauseEdit = UIFactory::makeEditText("normal", 600, 595, sf::Color::White, 20);
			m_pauseEdit->setFocusColor(sf::Color::Black);
			m_pauseEdit->setText(Utils::getKeyName(currentOptions.getKey(Options::Up)));
			m_pauseEdit->setInputLimit(1, true);
			m_pauseEdit->connect(sf::Event::MouseButtonPressed, [this]() { m_pauseEdit->setFullFocus(true); });
			addUIObjects(m_pauseEdit);

			m_bombEdit = UIFactory::makeEditText("normal", 600, 660, sf::Color::White, 20);
			m_bombEdit->setFocusColor(sf::Color::Black);
			m_bombEdit->setText(Utils::getKeyName(currentOptions.getKey(Options::Up)));
			m_bombEdit->setInputLimit(1, true);
			m_bombEdit->connect(sf::Event::MouseButtonPressed, [this]() { m_bombEdit->setFullFocus(true); });
			addUIObjects(m_bombEdit);
	}

	void OptionState::update(float delta) {
	}

	void OptionState::handleEvents(sf::Event& event) {
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

		if(event.type == sf::Event::KeyPressed) {
			for(auto it = m_uiObjects.begin(), end = m_uiObjects.end(); it != end; ++it) {
				(*it)->emit(event);
			}
		}
	}

	void OptionState::changeGameState(const States::GameState newState) {
		Options::Option& currentOptions = m_profileLoader.getCurrentProfile().getOption();
		currentOptions.setKey(Options::Up, Utils::getKeyValue(m_upEdit->getText()));
		currentOptions.setKey(Options::Down, Utils::getKeyValue(m_downEdit->getText()));
		currentOptions.setKey(Options::Left, Utils::getKeyValue(m_leftEdit->getText()));
		currentOptions.setKey(Options::Right, Utils::getKeyValue(m_rightEdit->getText()));
		currentOptions.setKey(Options::Pause, Utils::getKeyValue(m_pauseEdit->getText()));
		currentOptions.setKey(Options::Bomb, Utils::getKeyValue(m_bombEdit->getText()));
		m_profileLoader.saveCurrentProfile();
		States::State::changeGameState(newState);
	}

	void OptionState::start() {
		resetFocus();
		/* Updating the labels accordingly to current profile */
		Options::Profile& currentProfile = m_profileLoader.getCurrentProfile();
		Options::Option& currentOption = currentProfile.getOption();

		m_musicLabel->setText(Utils::toString(currentProfile.getMusicLevel()));
		m_soundLabel->setText(Utils::toString(currentProfile.getSoundLevel()));
		m_upEdit->setText(Utils::getKeyName(currentOption.getKey(Options::Up)));
		m_downEdit->setText(Utils::getKeyName(currentOption.getKey(Options::Down)));
		m_leftEdit->setText(Utils::getKeyName(currentOption.getKey(Options::Left)));
		m_rightEdit->setText(Utils::getKeyName(currentOption.getKey(Options::Right)));
		m_pauseEdit->setText(Utils::getKeyName(currentOption.getKey(Options::Pause)));
		m_bombEdit->setText(Utils::getKeyName(currentOption.getKey(Options::Bomb)));
	}

	void OptionState::raiseMusic() {
		Options::Profile& currentProfile = m_profileLoader.getCurrentProfile();
		currentProfile.raiseMusicLevel();
		m_musicLabel->setText(Utils::toString(currentProfile.getMusicLevel()));
	}

	void OptionState::lowerMusic() {
		Options::Profile& currentProfile = m_profileLoader.getCurrentProfile();
		currentProfile.lowerMusicLevel();
		m_musicLabel->setText(Utils::toString(currentProfile.getMusicLevel()));
	}

	void OptionState::raiseSound() {
		Options::Profile& currentProfile = m_profileLoader.getCurrentProfile();
		currentProfile.raiseSoundLevel();
		m_soundLabel->setText(Utils::toString(currentProfile.getSoundLevel()));
	}

	void OptionState::lowerSound() {
		Options::Profile& currentProfile = m_profileLoader.getCurrentProfile();
		currentProfile.lowerSoundLevel();
		m_soundLabel->setText(Utils::toString(currentProfile.getSoundLevel()));
	}
}