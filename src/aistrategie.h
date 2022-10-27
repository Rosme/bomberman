#ifndef DATAMODEL_AISTRATEGIE_H
#define DATAMODEL_AISTRATEGIE_H

#include <list>
#include <vector>
#include <SFML/System.hpp>

namespace DataModel {

	class Map;
	class Player;

	class AIStrategie {
	protected:
		typedef std::list<sf::Vector2i> Path;
		typedef std::vector<Path> PathList;
		struct PathFinder {
			bool operator() (Path a, Path b) {
				return (a.size() < b.size());
			}
		};
		static const unsigned int DECISION_LIMIT;
		
	public:
		AIStrategie();
        virtual ~AIStrategie();

		virtual void update(DataModel::Map& map, DataModel::Player& owner) = 0;
	};

}

#endif
