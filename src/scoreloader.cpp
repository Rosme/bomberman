#include <algorithm>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cereal/types/utility.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include "scoreloader.h"

namespace DataModel {

	namespace bfs = std::filesystem;

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
			cereal::BinaryInputArchive ia(ifs);
			ia(CEREAL_NVP(m_scores));
		}
	}

	void ScoreLoader::saveScores() {
		std::ofstream ofs(m_filePath + ".bpsc", std::ios::binary);
		
		cereal::BinaryOutputArchive oa(ofs);
		oa(CEREAL_NVP(m_scores));
	}
}