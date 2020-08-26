#include <SFML/Graphics.hpp>

#include "gamewindow.h"

int main() {
	//Seed initialisation for randomisation
	srand(static_cast<unsigned int>(time(nullptr)));
	sf::RenderWindow renderWindow(sf::VideoMode(900,800), "Bomberman", sf::Style::Close);
	renderWindow.setFramerateLimit(60);
	
	try {
		GameWindow gameWindow(renderWindow);

		while(renderWindow.isOpen()) {
			sf::Event event;
			while(renderWindow.pollEvent(event)) {
				gameWindow.handleEvents(event);
			}

			gameWindow.draw();
			gameWindow.update();
		}

	} catch(const std::exception& e) {
		sf::err() << e.what();
	}

	return EXIT_SUCCESS;
}