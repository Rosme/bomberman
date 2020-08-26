#ifndef DATAMODEL_MAPLOADER_H
#define DATAMODEL_MAPLOADER_H

#include <string>
#include <vector>

namespace DataModel {

	class Map;

	class MapLoader {
	private:
		std::string m_mapPath;
		
	public:
		/* Ctor */
		MapLoader(const std::string& mapPath);

		/* Methods */
		void saveMap(DataModel::Map& map); //Save the map to it's file
		void loadMap(const std::string& name, DataModel::Map& map); //Load the map from the file
		std::vector<std::string> loadMapList(); //List of all the map name
	};

}

#endif