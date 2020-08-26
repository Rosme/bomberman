#ifndef DATAMODEL_GAMEOBJECT_H
#define DATAMODEL_GAMEOBJECT_H

#include <memory>
#include <SFML/Graphics.hpp>

namespace DataModel {
	
	class GameObject {
	protected:
		sf::Sprite m_sprite;
		sf::Vector2i m_position;

		void updateSpritePosition(int xMargin = 0, int yMargin = 0);

	public:
		GameObject();
		GameObject(sf::Texture& texture, sf::IntRect subRect, sf::Vector2i position);
		virtual ~GameObject();

		void draw(sf::RenderTexture& renderTexture); //Draw the object
		sf::Vector2i getPosition(); //Return the position of the object on the map

		/* Virtual */
		virtual void setPosition(sf::Vector2i position); //Set the position
		virtual void setTexture(sf::Texture& texture, sf::IntRect subRect); //Set the texture for the sprite
		virtual void update(); //Update the object accordingly
	};

	typedef std::shared_ptr<GameObject> GameObjectPtr;
}

#endif