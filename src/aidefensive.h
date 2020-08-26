#ifndef DATAMODEL_AIDEFENSIVE_H
#define DATAMODEL_AIDEFENSIVE_H

#include <list>
#include "aistrategie.h"
#include "timer.h"

namespace DataModel {

	class AIDefensive : public DataModel::AIStrategie {
	private:
		Utils::Timer m_changePathTimer,
					 m_decisionTimer;
		Path m_currentPath;

		sf::Vector2i findBestPosition(DataModel::Map& map, sf::Vector2i ownPos, sf::Vector2i runPos);
		AIStrategie::Path getPath(DataModel::Map& map, DataModel::Player& owner);
	public:
		AIDefensive();

		void update(DataModel::Map& map, DataModel::Player& owner); //What do now?
	};

}

#endif