#include "editorstate.h"
#include "gamewindow.h"
#include "tile.h"

namespace States {

	EditorState::EditorState(GameWindow& gameWindow, std::shared_ptr<Ressources::Manager> ressources, DataModel::MapLoader& mapLoader)
		: States::State(gameWindow), 
		m_seperator(sf::Vector2f(3, 300)), 
		m_map(ressources), 
		m_ressources(ressources),
		m_currentTile(DataModel::Tile::Ground),
		m_mapLoader(mapLoader),
		m_currentSubstate(EditorState::None) {
			if(!m_headerTexture.create(gameWindow.WIDTH, 100)) {
				throw std::runtime_error("Couldn't create the Header Texture for Editor");
			}
			if(!m_mapTexture.create(864, 672)) {
				throw std::runtime_error("Couldn't create the Map Texture for Editor");
			}
			if(!m_newMapTexture.create(300, 150)) {
				throw std::runtime_error("Couldn't create the New Map Texture for Editor");
			}
			if(!m_loadMapTexture.create(270, 400)) {
				throw std::runtime_error("Couldn't create the Load Map Texture for Editor");
			}

			/* Header Setup */
			m_headerSprite.setTexture(m_headerTexture.getTexture());

			sf::Texture& tileTexture = ressources->getTexture("tiles");
			sf::Sprite groundTile(tileTexture);
			groundTile.setTextureRect(sf::IntRect(DataModel::Tile::SIZE*3, DataModel::Tile::SIZE*0, DataModel::Tile::SIZE, DataModel::Tile::SIZE));
			groundTile.setPosition(30, 30);
			m_tileSprite.push_back(groundTile);

			sf::Sprite grassTile(tileTexture);
			grassTile.setTextureRect(sf::IntRect(DataModel::Tile::SIZE*2, DataModel::Tile::SIZE*0, DataModel::Tile::SIZE, DataModel::Tile::SIZE));
			grassTile.setPosition(80, 30);
			m_tileSprite.push_back(grassTile);
			
			sf::Sprite wallTile(tileTexture);
			wallTile.setTextureRect(sf::IntRect(DataModel::Tile::SIZE*0, DataModel::Tile::SIZE*0, DataModel::Tile::SIZE, DataModel::Tile::SIZE));
			wallTile.setPosition(130, 30);
			m_tileSprite.push_back(wallTile);

			sf::Sprite brickTile(tileTexture);
			brickTile.setTextureRect(sf::IntRect(DataModel::Tile::SIZE*0, DataModel::Tile::SIZE*1, DataModel::Tile::SIZE, DataModel::Tile::SIZE));
			brickTile.setPosition(180, 30);
			m_tileSprite.push_back(brickTile);

			sf::Texture& playerTexture = ressources->getTexture("players");
			sf::Sprite player1(playerTexture);
			player1.setTextureRect(sf::IntRect(0, 0, 32, 45));
			player1.setPosition(500, 30);
			m_playersSprite.push_back(player1);			

			sf::Sprite player2(playerTexture);
			player2.setTextureRect(sf::IntRect(0, 45, 32, 45));
			player2.setPosition(550, 30);
			m_playersSprite.push_back(player2);

			sf::Sprite player3(playerTexture);
			player3.setTextureRect(sf::IntRect(0, 90, 32, 45));
			player3.setPosition(600, 30);
			m_playersSprite.push_back(player3);

			sf::Sprite player4(playerTexture);
			player4.setTextureRect(sf::IntRect(0, 135, 32, 45));
			player4.setPosition(650, 30);
			m_playersSprite.push_back(player4);

			m_seperator.setFillColor(sf::Color::Black);
			m_seperator.setOutlineColor(sf::Color::Black);
			m_seperator.setPosition(700, 0);
			
			Buttonptr newButton = UIFactory::makeButton("New", "option-button", 730, 15, sf::Color::Black, sf::Color::White, sf::Color::Black, 20);
			newButton->setFocusTextColor(sf::Color::White);
			newButton->setFocusFillColor(sf::Color::Black);
			newButton->setFocusOutlineColor(sf::Color::White);
			newButton->connect(sf::Event::MouseButtonPressed, [this]() { m_map.resetMap(); });
			addUIObjects(newButton);

			Buttonptr saveButton = UIFactory::makeButton("Save", "option-button", 830, 15, sf::Color::Black, sf::Color::White, sf::Color::Black, 20);
			saveButton->setFocusTextColor(sf::Color::White);
			saveButton->setFocusFillColor(sf::Color::Black);
			saveButton->setFocusOutlineColor(sf::Color::White);
			saveButton->connect(sf::Event::MouseButtonPressed, [this]() { this->setCurrentSubstate(EditorState::Save); });
			addUIObjects(saveButton);

			Buttonptr loadButton = UIFactory::makeButton("Load", "option-button", 730, 65, sf::Color::Black, sf::Color::White, sf::Color::Black, 20);
			loadButton->setFocusTextColor(sf::Color::White);
			loadButton->setFocusFillColor(sf::Color::Black);
			loadButton->setFocusOutlineColor(sf::Color::White);
			loadButton->connect(sf::Event::MouseButtonPressed, [this]() { this->loadMapList(); });
			addUIObjects(loadButton);

			Buttonptr quitButton = UIFactory::makeButton("Quit", "option-button", 830, 65, sf::Color::Black, sf::Color::White, sf::Color::Black, 20);
			quitButton->setFocusTextColor(sf::Color::White);
			quitButton->setFocusFillColor(sf::Color::Black);
			quitButton->setFocusOutlineColor(sf::Color::White);
			quitButton->connect(sf::Event::MouseButtonPressed, [this]() { this->changeGameState(States::Menu); });
			addUIObjects(quitButton);

			/* Map Setup */
			m_mapSprite.setTexture(m_mapTexture.getTexture());
			m_mapSprite.setPosition((gameWindow.WIDTH/2)-(m_mapSprite.getGlobalBounds().width/2), (gameWindow.HEIGHT/2)-(m_mapSprite.getGlobalBounds().height/2)+50);

			/* New Map Setup */
			m_newMapSprite.setTexture(m_newMapTexture.getTexture());
			m_newMapSprite.setPosition((m_gameWindow.WIDTH/2)-(m_newMapSprite.getGlobalBounds().width/2), (m_gameWindow.HEIGHT/2)-(m_newMapSprite.getGlobalBounds().height/2));
			m_newMapObjects.push_back(UIFactory::makeLabel("New Map Name", "important", 10, 5, sf::Color::White));
			m_mapNameEdit = UIFactory::makeEditText("normal", 50, 50, sf::Color::White, 20);
			m_mapNameEdit->setFocusColor(sf::Color::Black);
			m_mapNameEdit->connect(sf::Event::MouseButtonPressed, [this](){ m_mapNameEdit->setFullFocus(true); });
			m_mapNameEdit->setFullFocus(true);
			m_mapNameEdit->setInputLimit(15);
			m_mapNameEdit->setKeyFilter(UI::EditText::AlphaNum);
			m_newMapObjects.push_back(m_mapNameEdit);

			/* Load Map Setup */
			m_loadMapSprite.setTexture(m_loadMapTexture.getTexture());
			m_loadMapSprite.setPosition((m_gameWindow.WIDTH/2)-(m_loadMapSprite.getGlobalBounds().width/2), (m_gameWindow.HEIGHT/2)-(m_loadMapSprite.getGlobalBounds().height/2));
	}

	void EditorState::update(float delta) {
	}

	void EditorState::handleEvents(sf::Event& event) {
		switch(m_currentSubstate) {
		case EditorState::None:
			handleNoneSubstateEvents(event);
			break;
		case EditorState::Save:
			handleSaveSubstateEvents(event);
			break;
		case EditorState::Load:
			handleLoadSubstateEvents(event);
			break;
		}
	}

	void EditorState::start() {
		resetFocus();
		setCurrentSubstate(EditorState::None);
		m_map.resetMap();
	}

	void EditorState::draw(sf::RenderTexture& renderTexture) {
		m_headerTexture.clear(sf::Color(181, 230, 29));
		States::State::draw(m_headerTexture);
		for(auto it = m_tileSprite.begin(), end = m_tileSprite.end(); it  != end; ++it) {
			m_headerTexture.draw(*it);
		}
		for(auto it = m_playersSprite.begin(), end = m_playersSprite.end(); it != end; ++it) {
			m_headerTexture.draw(*it);
		}
		m_headerTexture.draw(m_seperator);
		m_headerTexture.display();

		m_mapTexture.clear();
		m_map.draw(m_mapTexture);
		m_map.drawPlayer(m_mapTexture);
		m_mapTexture.display();

		renderTexture.draw(m_headerSprite);
		renderTexture.draw(m_mapSprite);

		if(m_currentSubstate == EditorState::Save) {
			m_newMapTexture.clear(sf::Color(0, 119, 170));

			for(auto it = m_newMapObjects.begin(), end = m_newMapObjects.end(); it != end; ++it) {
				(*it)->draw(m_newMapTexture);
			}

			m_newMapTexture.display();
			renderTexture.draw(m_newMapSprite);
		} else if(m_currentSubstate == EditorState::Load) {
			m_loadMapTexture.clear(sf::Color(0, 119, 170));

			for(auto it = m_loadMapObjects.begin(), end = m_loadMapObjects.end(); it != end; ++it) {
				(*it)->draw(m_loadMapTexture);
			}

			m_loadMapTexture.display();
			renderTexture.draw(m_loadMapSprite);
		}
	}

	void EditorState::changeCurrentTileType(DataModel::Tile::Type type) {
		m_currentTile = type;
	}

	void EditorState::setTileToMap(sf::Vector2i position) {
		m_map.setTile(m_currentTile, position);
	}

	sf::Vector2i EditorState::toMapPosition(sf::Vector2f mousePosition) {
		return sf::Vector2i(static_cast<unsigned int>((mousePosition.x-m_mapSprite.getGlobalBounds().left)/DataModel::Tile::SIZE),
							static_cast<unsigned int>((mousePosition.y-m_mapSprite.getGlobalBounds().top)/DataModel::Tile::SIZE));
	}

	void EditorState::saveMap(const std::string& name) {
		m_map.setName(name);
		m_mapLoader.saveMap(m_map);
		m_mapNameEdit->resetText();
	}

	void EditorState::loadMap(const std::string& name) {
		m_mapLoader.loadMap(name, m_map);
		m_map.updateTileTexture();
		setCurrentSubstate(EditorState::None);
	}

	void EditorState::loadMapList() {
		auto mapList = m_mapLoader.loadMapList();
		m_loadMapObjects.erase(m_loadMapObjects.begin(), m_loadMapObjects.end());

		m_loadMapObjects.push_back(UIFactory::makeLabel("Map list", "important", 20, 0, sf::Color::White));

		for(unsigned int i = 0, j = 1; i < mapList.size(); ++i) {
			Labelptr mapName = UIFactory::makeLabel(mapList[i], "normal", static_cast<float>((m_loadMapSprite.getGlobalBounds().width/2)-100), static_cast<float>(((j*20)+25)), sf::Color::White, 20);
			mapName->setFocusColor(sf::Color::Black);
			mapName->connect(sf::Event::MouseButtonPressed, [this, mapName]() { loadMap(mapName->getText()); });
			m_loadMapObjects.push_back(mapName);
			++j;
		}

		setCurrentSubstate(EditorState::Load);
	}

	void EditorState::handleNoneSubstateEvents(sf::Event& event) {
		if(event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
			case sf::Keyboard::Escape:
				changeGameState(States::Menu);
				break;
			case sf::Keyboard::Num1:
			case sf::Keyboard::Numpad1:
				changeCurrentTileType(DataModel::Tile::Ground);
				break;
			case sf::Keyboard::Num2:
			case sf::Keyboard::Numpad2:
				changeCurrentTileType(DataModel::Tile::Grass);
				break;
			case sf::Keyboard::Num3:
			case sf::Keyboard::Numpad3:
				changeCurrentTileType(DataModel::Tile::Wall);
				break;
			case sf::Keyboard::Num4:
			case sf::Keyboard::Numpad4:
				changeCurrentTileType(DataModel::Tile::Brick);
				break;
			case sf::Keyboard::Num5:
			case sf::Keyboard::Numpad5:
				m_playerChose.first = true;
				m_playerChose.second = 0;
				break;
			case sf::Keyboard::Num6:
			case sf::Keyboard::Numpad6:
				m_playerChose.first = true;
				m_playerChose.second = 1;
				break;
			case sf::Keyboard::Num7:
			case sf::Keyboard::Numpad7:
				m_playerChose.first = true;
				m_playerChose.second = 2;
				break;
			case sf::Keyboard::Num8:
			case sf::Keyboard::Numpad8:
				m_playerChose.first = true;
				m_playerChose.second = 3;
				break;
			case sf::Keyboard::S:
				setCurrentSubstate(EditorState::Save);
				break;
			case sf::Keyboard::L:
				loadMapList();
				break;
			case sf::Keyboard::N:
				m_map.resetMap();
				break;
			}
		}

		if(event.type == sf::Event::MouseMoved) {
			sf::Vector2f mousePosition(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
			if(m_mouseDownOnMap && m_mapSprite.getGlobalBounds().contains(mousePosition)) {
				sf::Vector2i mapPosition(toMapPosition(mousePosition));
				setTileToMap(mapPosition);
			} else {
				for(auto it = m_uiObjects.begin(), end = m_uiObjects.end(); it != end; ++it) {
					sf::FloatRect bounds = (*it)->getBoundings();
					if(bounds.contains(mousePosition)) {
						(*it)->setFocus(true);
					} else {
						(*it)->setFocus(false);
					}
				}
			}
		}

		if(event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
			if(m_mapSprite.getGlobalBounds().contains(mousePosition)) {
				sf::Vector2i mapPosition(toMapPosition(mousePosition));
				if(m_playerChose.first) {
					m_map.setPlayerPosition(m_playerChose.second, mapPosition);
					m_playerChose.first = false;
				} else {
					m_mouseDownOnMap = true;
					setTileToMap(mapPosition);
				}

			} else {
				for(auto it = m_uiObjects.begin(), end = m_uiObjects.end(); it != end; ++it) {
					sf::FloatRect bounds = (*it)->getBoundings();
					if(bounds.contains(mousePosition)) {
						(*it)->emit(event);
					}
				}
				for(unsigned int i = 0; i < m_tileSprite.size(); ++i) {
					if(m_tileSprite[i].getGlobalBounds().contains(mousePosition)) {
						switch(i) {
						case 0:
							changeCurrentTileType(DataModel::Tile::Ground);
							break;
						case 1:
							changeCurrentTileType(DataModel::Tile::Grass);
							break;
						case 2:
							changeCurrentTileType(DataModel::Tile::Wall);
							break;
						case 3:
							changeCurrentTileType(DataModel::Tile::Brick);
							break;
						}
					}
					m_playerChose.first = false;
				}
				for(unsigned int i = 0; i < m_playersSprite.size(); ++i) {
					if(m_playersSprite[i].getGlobalBounds().contains(mousePosition)) {
						m_playerChose.first = true;
						m_playerChose.second = i;
					}
				}
			}
		}

		if(event.type == sf::Event::MouseButtonReleased) {
			m_mouseDownOnMap = false;
		}
	}

	void EditorState::handleSaveSubstateEvents(sf::Event& event) {
		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Escape) {
				setCurrentSubstate(EditorState::None);
			} else if(event.key.code == sf::Keyboard::Return) {
				std::string name = m_mapNameEdit->getText();
				name.erase(std::remove_if(name.begin(), name.end(), ::isspace));
				if(name.empty() || name == "...") {
					m_mapNameEdit->setFullFocus(true);
					m_mapNameEdit->resetText();
				} else {
					saveMap(name);
					setCurrentSubstate(EditorState::None);
				}
			} else {
				m_mapNameEdit->emit(event);
			}
		}
		if(event.type == sf::Event::MouseButtonPressed) {
			sf::FloatRect bounds = m_mapNameEdit->getBoundings();
			bounds.left += m_newMapSprite.getPosition().x;
			bounds.top += m_newMapSprite.getPosition().y;
			if(bounds.contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
				m_mapNameEdit->emit(event);
			}
		}
	}

	void EditorState::handleLoadSubstateEvents(sf::Event& event) {
		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Escape) {
				setCurrentSubstate(EditorState::None);
			}
		}

		if(event.type == sf::Event::MouseMoved) {
			sf::Vector2f mousePosition(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
			for(auto it = m_loadMapObjects.begin(), end = m_loadMapObjects.end(); it != end; ++it) {
				sf::FloatRect bounds = (*it)->getBoundings();
				bounds.left += m_loadMapSprite.getPosition().x;
				bounds.top += m_loadMapSprite.getPosition().y;
				if(bounds.contains(mousePosition)) {
					(*it)->setFocus(true);
				} else {
					(*it)->setFocus(false);
				}
			}
		}

		if(event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
			for(auto it = m_loadMapObjects.begin(), end = m_loadMapObjects.end(); it != end; ++it) {
				sf::FloatRect bounds = (*it)->getBoundings();
				bounds.left += m_loadMapSprite.getPosition().x;
				bounds.top += m_loadMapSprite.getPosition().y;
				if(bounds.contains(mousePosition)) {
					(*it)->emit(event);
				}
			}
		}
	}

	void EditorState::setCurrentSubstate(Substate substate) {
		m_currentSubstate = substate;
		resetFocus();
	}
}