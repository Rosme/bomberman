#include <algorithm>
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>
#include "scoreloader.h"

namespace DataModel {

	namespace bfs = boost::filesystem;

	ScoreLoader::ScoreLoader(const std::string& filePath)
		: m_filePath(filePath) {
	}

	void ScoreLoader::addScore(ScoreEntry entry) {
		m_scores.push_back(entry);
		std::sort(m_scores.begin(), m_scores.end(), ScoreComparator());

		while(m_scores.size() > 10) {
			m_scores.pop_back();
		}

		//Now that we're up to date with scores, save time
		saveScores();
	}

	ScoreArray& ScoreLoader::getScores() {
		return m_scores;
	}

	void ScoreLoader::loadScores() {
		//Score file exists, not the first time
		if(bfs::exists(bfs::path(m_filePath + ".bpsc"))) {
			std::cout << "Score\n";
			std::ifstream ifs(m_filePath + ".bpsc", std::ios::binary);
			boost::archive::binary_iarchive ia(ifs);
			ia >> BOOST_SERIALIZATION_NVP(m_scores);
		}
	}

	void ScoreLoader::saveScores() {
		std::ofstream ofs(m_filePath + ".bpsc", std::ios::binary);
		
		boost::archive::binary_oarchive oa(ofs);
		oa << BOOST_SERIALIZATION_NVP(m_scores);
	}
}