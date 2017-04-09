#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "maploader.h"
#include "map.h"
#include "aicrazy.h"
#include "aioffensive.h"
#include "aidefensive.h"

namespace DataModel {
	
	namespace bfs = boost::filesystem;

	MapLoader::MapLoader(const std::string& mapPath)
		: m_mapPath(mapPath) {
			bfs::path directory(m_mapPath);

			if(!bfs::exists(directory)) {
				bfs::create_directory(directory);
			}
		}

	void MapLoader::saveMap(DataModel::Map& map) {
		
		std::ofstream ofs(m_mapPath + map.getName() + ".mp");
		
		boost::archive::xml_oarchive oa(ofs);
		oa << BOOST_SERIALIZATION_NVP(map);
	}

	void MapLoader::loadMap(const std::string& name, DataModel::Map& map) {

		std::ifstream ifs(m_mapPath + name + ".mp");

		boost::archive::xml_iarchive ia(ifs);
		ia >> BOOST_SERIALIZATION_NVP(map);

		//Id attribution
		map.getPlayer(0).setId(1);
		map.getPlayer(1).setId(2);
		map.getPlayer(2).setId(3);
		map.getPlayer(3).setId(4);

		//AI Attribution
		map.getPlayer(0).setStrategie(nullptr);
		map.getPlayer(1).setStrategie(new DataModel::AIOffensive());
		map.getPlayer(2).setStrategie(new DataModel::AIDefensive());
		map.getPlayer(3).setStrategie(new DataModel::AICrazy());
	}

	std::vector<std::string> MapLoader::loadMapList() {
		bfs::path path(m_mapPath);
		std::vector<std::string> mapList;

		for(auto it = bfs::directory_iterator(path), end = bfs::directory_iterator(); it != end; ++it) {
			if((*it).path().extension().string() == ".mp") {
				mapList.push_back((*it).path().stem().string());
			}
		}

		return mapList;
	}
}