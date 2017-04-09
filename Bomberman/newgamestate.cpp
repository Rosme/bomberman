#include <algorithm>
#include <boost/random.hpp>
#include <boost/bind.hpp>
#include "newgamestate.h"
#include "profile.h"
#include "player.h"
#include "utils.h"
#include "bomb.h"

namespace States {

	/* New Game State */
	NewGameState::NewGameState(GameWindow& gameWindow, DataModel::MapLoader& mapLoader)
		: States::State(gameWindow), m_mapLoader(mapLoader), m_subState(new PlayingState(gameWindow, mapLoader, this)), m_playing(false) {
			addUIObjects(UIFactory::makeLabel("New Game", "important", 50, 10, sf::Color::White, 50));
			addUIObjects(UIFactory::makeLabel("Choose what you want to do!", "important", 250, 70, sf::Color::White, 35));
			addUIObjects(UIFactory::makeLabel("Load the map you want", "important", 80, 150, sf::Color::White, 27));
			addUIObjects(UIFactory::makeLabel("or", "important", 380, 150, sf::Color::White, 27));
			addUIObjects(UIFactory::makeLabel("Go with a random map", "important", 500, 150, sf::Color::White, 27));

			//Random map label
			Labelptr randomMapLabel = UIFactory::makeLabel("Random", "normal", 575, 400, sf::Color::Black, 25);
			randomMapLabel->setFocusColor(sf::Color::White);
			randomMapLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::NewGameState::loadRandomMap, boost::ref(*this)));
			addUIObjects(randomMapLabel);

			//Back label
			Labelptr backLabel = UIFactory::makeLabel("Back to main menu", "normal", 20, 750, sf::Color::Black, 20);
			backLabel->setFocusColor(sf::Color::White);
			backLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::State::changeGameState, boost::ref(*this), States::Menu));
			addUIObjects(backLabel);
	}

	
	void NewGameState::update(float delta) {
		if(m_playing) {
			m_subState->update(delta);
		}
	}

	void NewGameState::handleEvents(sf::Event& event) {
		if(m_playing) {
			m_subState->handleEvents(event);
		} else {
			if(event.type == sf::Event::KeyPressed) {
				switch(event.key.code) {
				case sf::Keyboard::Escape:
					changeGameState(States::Menu);
					break;
				case sf::Keyboard::R:
					loadRandomMap();
					break;
				}
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

				for(auto it = m_mapListLabel.begin(), end = m_mapListLabel.end(); it != end; ++it) {
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

				for(auto it = m_mapListLabel.begin(), end = m_mapListLabel.end(); it != end; ++it) {
					sf::FloatRect bounds = (*it)->getBoundings();
					if(bounds.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
						(*it)->emit(event);
					}
				}
			}
		}
	}

	void NewGameState::start() {
		resetFocus();
		m_playing = false;
		auto mapList = m_mapLoader.loadMapList();
		m_mapListLabel.clear();
		for(unsigned int i = 0; i < mapList.size(); ++i) {
			Labelptr map = UIFactory::makeLabel(mapList[i], "normal", 150, static_cast<float>((i*30)+200), sf::Color::Black, 25);
			map->setFocusColor(sf::Color::White);
			map->connect(sf::Event::MouseButtonPressed, boost::bind(&States::NewGameState::startPlaying, boost::ref(*this), map->getText()));
			m_mapListLabel.push_back(map);
		}

	}

	void NewGameState::draw(sf::RenderTexture& renderTexture) {
		if(m_playing) {
			m_subState->draw(renderTexture);
		} else {
			States::State::draw(renderTexture);

			for(auto it = m_mapListLabel.begin(), end = m_mapListLabel.end(); it != end; ++it) {
				(*it)->draw(renderTexture);
			}
		}
	}

	void NewGameState::startPlaying(const std::string& mapName) {
		m_playing = true;
		dynamic_cast<States::PlayingState*>(m_subState.get())->setMap(mapName);
		m_subState->start();
	}

	void NewGameState::stopPlaying() {
		m_playing = false;
		start();
	}

	void NewGameState::loadRandomMap() {
		auto mapList = m_mapLoader.loadMapList();
		std::random_shuffle(mapList.begin(), mapList.end());
		startPlaying(mapList[0]);
	}

	/* Playing State */

	/* Static Initialisation */

	const unsigned int PlayingState::DESTRUCTION_SCORE = 5;
	const unsigned int PlayingState::PLAYER_SCORE = 15;
	const unsigned int PlayingState::POWERUP_SCORE = 10;

	PlayingState::PlayingState(GameWindow& gameWindow, DataModel::MapLoader& mapLoader, States::NewGameState* parent)
		: States::State(gameWindow), 
		m_mapLoader(mapLoader), 
		m_map(gameWindow.getRessourcesManager()), 
		m_parent(parent), 
		m_gen(static_cast<unsigned int>(time(nullptr))),
		m_seperator(sf::Vector2f(3, 300)),
		m_currentPlayerScore(10000),
		m_firstGame(true),
		m_paused(false) {

		if(!m_mapTexture.create(864, 672)) {
			throw std::runtime_error("Couldn't create the Map Texture for the Game");
		}

		if(!m_headerTexture.create(gameWindow.WIDTH, 100)) {
			throw std::runtime_error("Couldn't create the Header Texture for the Game");
		}

		if(!m_pausedTexture.create(300, 100)) {
			throw std::runtime_error("Couldn't create the Paused Texture for the Game");
		}

		m_mapSprite.setTexture(m_mapTexture.getTexture());
		m_mapSprite.setPosition((gameWindow.WIDTH/2)-(m_mapSprite.getGlobalBounds().width/2), (gameWindow.HEIGHT/2)-(m_mapSprite.getGlobalBounds().height/2)+50);

		/* Header Setup */
		m_headerSprite.setTexture(m_headerTexture.getTexture());

		auto& ressources = gameWindow.getRessourcesManager();

		sf::Texture& playerTexture = ressources->getTexture("players");
		sf::Sprite player1(playerTexture);
		player1.setTextureRect(sf::IntRect(0, 0, 32, 45));
		player1.setPosition(10, 20);
		m_headerSprites.push_back(player1);			

		sf::Sprite player2(playerTexture);
		player2.setTextureRect(sf::IntRect(0, 45, 32, 45));
		player2.setPosition(270, 20);
		m_headerSprites.push_back(player2);

		sf::Sprite player3(playerTexture);
		player3.setTextureRect(sf::IntRect(0, 90, 32, 45));
		player3.setPosition(470, 30);
		m_headerSprites.push_back(player3);

		sf::Sprite player4(playerTexture);
		player4.setTextureRect(sf::IntRect(0, 135, 32, 45));
		player4.setPosition(670, 30);
		m_headerSprites.push_back(player4);

		sf::Texture& powerUpTexture = ressources->getTexture("items");
		sf::Sprite bomb(powerUpTexture);
		bomb.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
		bomb.setPosition(50, 65);
		m_headerSprites.push_back(bomb);

		sf::Sprite fire(powerUpTexture);
		fire.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
		fire.setPosition(150, 65);
		m_headerSprites.push_back(fire);

		m_seperator.setFillColor(sf::Color::Black);
		m_seperator.setOutlineColor(sf::Color::Black);
		m_seperator.setPosition(250, 0);

		addUIObjects(UIFactory::makeLabel(gameWindow.getCurrentProfile().getName(), "normal", 80, 5, sf::Color::Black, 20));
		addUIObjects(UIFactory::makeLabel("Comp 1", "normal", 360, 5, sf::Color::Black, 20));
		addUIObjects(UIFactory::makeLabel("Comp 2", "normal", 560, 5, sf::Color::Black, 20));
		addUIObjects(UIFactory::makeLabel("Comp 3", "normal", 760, 5, sf::Color::Black, 20));

		m_playersLife.push_back(UIFactory::makeLabel("Life: ", "normal", 50, 35, sf::Color::Black, 18));
		m_playersLife.push_back(UIFactory::makeLabel("Life: ", "normal", 310, 35, sf::Color::Black, 18));
		m_playersLife.push_back(UIFactory::makeLabel("Life: ", "normal", 510, 35, sf::Color::Black, 18));
		m_playersLife.push_back(UIFactory::makeLabel("Life: ", "normal", 710, 30, sf::Color::Black, 18));
		m_playerBombLvl = UIFactory::makeLabel("3", "normal", 90, 70, sf::Color::Black, 20);
		m_playerFireLvl = UIFactory::makeLabel("3", "normal", 190, 70, sf::Color::Black, 20);
		m_playerScore = UIFactory::makeLabel("Score: ", "normal", 140, 35, sf::Color::Black, 18);

		/* Paused Texture Setup */
		m_pausedLabel.push_back(UIFactory::makeLabel("Pause", "normal", 120, 3, sf::Color::Black));

		Labelptr continueLabel = UIFactory::makeLabel("Continue", "normal", 30, 40, sf::Color::Black, 18);
		continueLabel->setFocusColor(sf::Color::White);
		continueLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::PlayingState::pauseGame, boost::ref(*this)));
		m_pausedLabel.push_back(continueLabel);

		Labelptr quitLabel = UIFactory::makeLabel("Quit", "normal", 220, 40, sf::Color::Black, 18);
		quitLabel->setFocusColor(sf::Color::White);
		quitLabel->connect(sf::Event::MouseButtonPressed, boost::bind(&States::NewGameState::stopPlaying, boost::ref(*m_parent)));
		m_pausedLabel.push_back(quitLabel);

		m_pausedSprite.setTexture(m_pausedTexture.getTexture());
		m_pausedSprite.setPosition((gameWindow.WIDTH/2)-(m_pausedSprite.getGlobalBounds().width/2), (gameWindow.HEIGHT/2)-(m_pausedSprite.getGlobalBounds().height/2)+50);
	}

	void PlayingState::update(float delta) {
		if(!m_paused) {
			if(m_map.getPlayer(0).isDead()) {
				m_firstGame = true;
				m_parent->stopPlaying();
				m_gameWindow.getScoreLoader().addScore(std::make_pair(m_gameWindow.getCurrentProfile().getName(), 
																	  m_currentPlayerScore));
			}
			if(m_map.getPlayer(1).isDead() && m_map.getPlayer(2).isDead() && m_map.getPlayer(3).isDead()) {
				m_parent->loadRandomMap();
			}
			m_map.update(*this);

			for(std::size_t i = 0, size = m_playersLife.size(); i < size; ++i) {
				m_playersLife[i]->setText("Life: " + Utils::toString(m_map.getPlayer(i).getRemainingLife()));
			}

			m_playerBombLvl->setText(Utils::toString(m_map.getPlayer(0).getBombQuantity()));
			m_playerFireLvl->setText(Utils::toString(m_map.getPlayer(0).getBombLevel()));
			m_playerScore->setText("Score: " + Utils::toString(m_currentPlayerScore));

			Options::Option& playersOption = m_gameWindow.getCurrentProfile().getOption();
			DataModel::Player& player = m_map.getPlayer(0);
			if(sf::Keyboard::isKeyPressed(playersOption.getKey(Options::Left))) {
				sf::Vector2i tilePosition = player.getPosition();
				--tilePosition.x;
				if(m_map.getTile(tilePosition).getProperty() & DataModel::Tile::Walkable) {
					player.move(DataModel::Player::Left);
				}
			}
			if(sf::Keyboard::isKeyPressed(playersOption.getKey(Options::Right))) {
				sf::Vector2i tilePosition = player.getPosition();
				++tilePosition.x;
				if(m_map.getTile(tilePosition).getProperty() & DataModel::Tile::Walkable) {
					player.move(DataModel::Player::Right);
				}
			}
			if(sf::Keyboard::isKeyPressed(playersOption.getKey(Options::Up))) {
				sf::Vector2i tilePosition = player.getPosition();
				--tilePosition.y;
				if(m_map.getTile(tilePosition).getProperty() & DataModel::Tile::Walkable) {
					player.move(DataModel::Player::Up);
				}
			}
			if(sf::Keyboard::isKeyPressed(playersOption.getKey(Options::Down))) {
				sf::Vector2i tilePosition = player.getPosition();
				++tilePosition.y;
				if(m_map.getTile(tilePosition).getProperty() & DataModel::Tile::Walkable) {
					player.move(DataModel::Player::Down);
				}
			}
			if(sf::Keyboard::isKeyPressed(playersOption.getKey(Options::Bomb)) && player.canPlaceBomb()) {
				player.placeBomb();
				m_map.placeBomb(DataModel::Bomb::White, player.getPosition(), player.getBombLevel());
			}

			for(auto it = m_fires.begin(), end = m_fires.end(); it != end; ++it) {
				if((*it)->lifeTimer.isExpired()) {
					it = m_fires.erase(it);
				}

				if(it == end) {
					break;
				}
			}
		} else {

		}
	}

	void PlayingState::handleEvents(sf::Event& event) {
		if(event.type == sf::Event::KeyPressed) {
			Options::Option& playersOption = m_gameWindow.getCurrentProfile().getOption();
			if(event.key.code == playersOption.getKey(Options::Pause)) {
				//m_parent->stopPlaying();
				pauseGame();
			}
		}

		if(m_paused) {
			if(event.type == sf::Event::MouseMoved) {
				for(auto it = m_pausedLabel.begin(), end = m_pausedLabel.end(); it != end; ++it) {
					sf::FloatRect bounds = (*it)->getBoundings();
					bounds.left += m_pausedSprite.getPosition().x;
					bounds.top += m_pausedSprite.getPosition().y;
					if(bounds.contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y))) {
						(*it)->setFocus(true);
					} else {
						(*it)->setFocus(false);
					}
				}
			}
			if(event.type == sf::Event::MouseButtonPressed) {
				for(auto it = m_pausedLabel.begin(), end = m_pausedLabel.end(); it != end; ++it) {
					sf::FloatRect bounds = (*it)->getBoundings();
					bounds.left += m_pausedSprite.getPosition().x;
					bounds.top += m_pausedSprite.getPosition().y;
					if(bounds.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
						(*it)->emit(event);
					}
				}
			}
		}
	}

	void PlayingState::start() {
		//m_bombs.clear();
		m_fires.clear();
		m_map.clear();
		for(std::size_t i = 0, size = m_playersLife.size(); i < size; ++i) {
			m_playersLife[i]->setText("Life: " + Utils::toString(m_map.getPlayer(i).getRemainingLife()));
		}
		m_playerBombLvl->setText(Utils::toString(m_map.getPlayer(0).getBombQuantity()));
		m_playerFireLvl->setText(Utils::toString(m_map.getPlayer(0).getBombLevel()));
		if(m_firstGame) {
			m_currentPlayerScore = 0;
			m_firstGame = false;
		}
	}

	void PlayingState::draw(sf::RenderTexture& renderTexture) {
		States::State::draw(renderTexture);

		m_headerTexture.clear(sf::Color(181, 230, 29));
		States::State::draw(m_headerTexture);
		for(auto it = m_headerSprites.begin(), end = m_headerSprites.end(); it != end; ++it) {
			m_headerTexture.draw(*it);
		}
		for(auto it = m_playersLife.begin(), end = m_playersLife.end(); it != end; ++it) {
			(*it)->draw(m_headerTexture);
		}
		m_playerBombLvl->draw(m_headerTexture);
		m_playerFireLvl->draw(m_headerTexture);
		m_playerScore->draw(m_headerTexture);
		m_headerTexture.draw(m_seperator);
		m_headerTexture.display();

		m_mapTexture.clear();
		m_map.draw(m_mapTexture);
		for(auto it = m_fires.begin(), end = m_fires.end(); it != end; ++it) {
			m_mapTexture.draw((*it)->sprite);
		}
		m_map.drawPlayer(m_mapTexture);
		m_mapTexture.display();

		renderTexture.draw(m_headerSprite);
		renderTexture.draw(m_mapSprite);

		if(m_paused) {
			m_pausedTexture.clear(sf::Color(0, 119, 170));
			for(auto it = m_pausedLabel.begin(), end = m_pausedLabel.end(); it != end; ++it) {
				(*it)->draw(m_pausedTexture);
			}
			m_pausedTexture.display();

			renderTexture.draw(m_pausedSprite);
		}
	}

	void PlayingState::setMap(const std::string& mapName) {
		m_mapLoader.loadMap(mapName, m_map);
		m_map.updateTileTexture();
	}

	void PlayingState::verifyExplosionCollision(int level, sf::Vector2i startPosition, int owner) {
		double prob[] = {0.6, 0.2, 0.2};
		boost::random::discrete_distribution<> dist(prob);

		int maxUp = ((startPosition.y - level) < 0) ? 0 : startPosition.y - level,
			maxDown = ((startPosition.y + level) > 21) ? 21 : startPosition.y + level,
			maxLeft = ((startPosition.x - level) < 0) ? 0 : startPosition.x - level,
			maxRight = ((startPosition.x + level) > 27) ? 27 : startPosition.x + level;

		auto& ressources = m_gameWindow.getRessourcesManager();
		m_fires.push_back(Ressources::makeFire(ressources->getTexture("fire"), sf::IntRect(0, 0, 32, 32), startPosition));

		std::vector<DataModel::Player*> players;
		for(unsigned int i = 0; i < 4; ++i) {
			players.push_back(&(m_map.getPlayer(i)));
		}

		//Up verification
		for(int i = startPosition.y; i >= maxUp; --i) {
			sf::Vector2i pos = startPosition;
			pos.y = i;
			if(i != startPosition.y) {
				m_fires.push_back(Ressources::makeFire(ressources->getTexture("fire"), sf::IntRect(32*2, 0, 32, 32), pos));
			}
			if(m_map.getTile(pos).getProperty() & DataModel::Tile::NotWalkable) {
				i = maxUp;
			}
			if(m_map.getTile(pos).getProperty() & DataModel::Tile::Destructible) {
				m_map.setTile(DataModel::Tile::Ground, pos);
				if(owner == 1) {
					raiseScore(DESTRUCTION_SCORE);
				}
				int powerUpResult = dist(m_gen);
				if(powerUpResult == 1) {
					m_map.placePowerUp(DataModel::Fire, pos);
				} else if(powerUpResult == 2) {
					m_map.placePowerUp(DataModel::BombQuantity, pos);
				}
			}
			verifyPlayerFireCollision(players.begin(), players.end(), pos, owner);
		}

		//Down verification
		for(int i = startPosition.y+1; i <= maxDown; ++i) {
			sf::Vector2i pos = startPosition;
			pos.y = i;
			if(i != startPosition.y) {
				m_fires.push_back(Ressources::makeFire(ressources->getTexture("fire"), sf::IntRect(32*2, 0, 32, 32), pos));
			}
			if(m_map.getTile(pos).getProperty() & DataModel::Tile::NotWalkable) {
				i = maxDown;
			}
			if(m_map.getTile(pos).getProperty() & DataModel::Tile::Destructible) {
				m_map.setTile(DataModel::Tile::Ground, pos);
				if(owner == 1) {
					raiseScore(DESTRUCTION_SCORE);
				}
				int powerUpResult = dist(m_gen);
				if(powerUpResult == 1) {
					m_map.placePowerUp(DataModel::Fire, pos);
				} else if(powerUpResult == 2) {
					m_map.placePowerUp(DataModel::BombQuantity, pos);
				}
			}
			verifyPlayerFireCollision(players.begin(), players.end(), pos, owner);
		}

		//Left verification
		for(int i = startPosition.x-1; i >= maxLeft; --i) {
			sf::Vector2i pos = startPosition;
			pos.x = i;
			if(i != startPosition.x) {
				m_fires.push_back(Ressources::makeFire(ressources->getTexture("fire"), sf::IntRect(32*1, 0, 32, 32), pos));
			}
			if(m_map.getTile(pos).getProperty() & DataModel::Tile::NotWalkable) {
				i = maxLeft;
			}
			if(m_map.getTile(pos).getProperty() & DataModel::Tile::Destructible) {
				m_map.setTile(DataModel::Tile::Ground, pos);
				if(owner == 1) {
					raiseScore(DESTRUCTION_SCORE);
				}
				int powerUpResult = dist(m_gen);
				if(powerUpResult == 1) {
					m_map.placePowerUp(DataModel::Fire, pos);
				} else if(powerUpResult == 2) {
					m_map.placePowerUp(DataModel::BombQuantity, pos);
				}
			}
			verifyPlayerFireCollision(players.begin(), players.end(), pos, owner);
		}

		//Right verification
		for(int i = startPosition.x+1; i <= maxRight; ++i) {
			sf::Vector2i pos = startPosition;
			pos.x = i;
			if(i != startPosition.x) {
				m_fires.push_back(Ressources::makeFire(ressources->getTexture("fire"), sf::IntRect(32*1, 0, 32, 32), pos));
			}
			if(m_map.getTile(pos).getProperty() & DataModel::Tile::NotWalkable) {
				i = maxRight;
			}
			if(m_map.getTile(pos).getProperty() & DataModel::Tile::Destructible) {
				m_map.setTile(DataModel::Tile::Ground, pos);	
				if(owner == 1) {
					raiseScore(DESTRUCTION_SCORE);
				}
				int powerUpResult = dist(m_gen);
				if(powerUpResult == 1) {
					//addPowerUp(DataModel::Fire, pos);
					m_map.placePowerUp(DataModel::Fire, pos);
				} else if(powerUpResult == 2) {
					//addPowerUp(DataModel::BombQuantity, pos);
					m_map.placePowerUp(DataModel::BombQuantity, pos);
				}
			}
			verifyPlayerFireCollision(players.begin(), players.end(), pos, owner);
		}
	}

	void PlayingState::verifyPlayerFireCollision(PlayerIterator begin, PlayerIterator end, sf::Vector2i position, unsigned int owner) {
		for(auto it = begin; it != end; ++it) {
			if((*it)->getPosition() == position) {
				if(owner == 1 && it != begin) {
					raiseScore(PLAYER_SCORE);
				}
				(*it)->removeLife();
			}
		}
	}

	void PlayingState::raiseScore(unsigned int amount) {
		m_currentPlayerScore += amount;
	}

	void PlayingState::pauseGame() {
		m_paused = !m_paused;
	}
}