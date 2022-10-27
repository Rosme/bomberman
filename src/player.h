#ifndef DATAMODEL_PLAYER_H
#define DATAMODEL_PLAYER_H

#include <vector>
#include <memory>
#include <cereal/access.hpp>
#include "gameobject.h"
#include "timer.h"
#include "aistrategie.h"

namespace DataModel {

	class Map;

	class Player : public GameObject {
		/* For serialization into file */
		friend class cereal::access;

		template<class Archive>
		void serialize(Archive & ar, const std::uint32_t /* file version */) {
			ar(m_position.x);
			ar(m_position.y);
		}

		unsigned int m_bombLevel; //Fire level of bombs
		Utils::Timer m_moveTimer; //Timer for movement to not got as fast as speed of light
		unsigned int m_maxBomb; //Max amount of bombs
		unsigned int m_currentBombQty; //Current amount of bomb placed
		Utils::Timer m_bombPlaceTimer; //Timer to for bomb placement between two placements
		std::vector<Utils::Timer> m_bombsTimer; //Timer for the reloads of bomb
		unsigned int m_lifes; //Amount of life
		std::unique_ptr<DataModel::AIStrategie> m_strategie;
		unsigned int m_id; //Player id
		
		void removeBomb();
	public:
		static const unsigned char MAX_BOMB_LEVEL;
		static const unsigned char MAX_BOMB_QUANTITY;
		enum Move {
			Up,
			Down,
			Left,
			Right
		};
		Player();
		Player(sf::Texture& texture, sf::IntRect subRect, sf::Vector2i position, unsigned int id);

		bool canPlaceBomb() const; //Verify if the player still has some bomb to place
		unsigned int getBombLevel() const; //Return the fire power
		unsigned int getBombQuantity() const; //Return the amount of bomb
		unsigned int getId() const; //Return his id
		unsigned int getRemainingLife() const; //Return the number of life left
		bool isDead() const; //nb of life == 0 ? You dead!
		void move(Player::Move direction); //I LIKE TO MOVE IT! MOVE IT!
		void placeBomb(); //Get to the CHOPPAA
		void raiseBombQuantity(); //More bomb? for me?
		void raiseFire(); //Bigger boom is better!
		void removeLife(); //Ouch, that hurts
		void setId(unsigned int id); //My number?
		void setPosition(sf::Vector2i position); //Where am i?
		void setStrategie(AIStrategie* strategie = nullptr); //What do I do?
		void updateMap(DataModel::Map& map); //Update to know what to do
	};

}

#endif
