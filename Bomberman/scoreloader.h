#ifndef DATAMODEL_SCORELOADER_H
#define DATAMODEL_SCORELOADER_H

#include <vector>
#include <string>

namespace DataModel {

	typedef std::pair<std::string, int> ScoreEntry;
	typedef std::vector<ScoreEntry> ScoreArray;

	class ScoreLoader {
	private:
		//Functor to order the array
		struct ScoreComparator {
			bool operator()(ScoreEntry i, ScoreEntry j) {
				return (i.second > j.second);
			}
		};

		 ScoreArray m_scores;
		 std::string m_filePath;

		 void saveScores();
	public:
		ScoreLoader(const std::string& filePath);

		void addScore(ScoreEntry entry); //Add a ScoreEntry to the array
		ScoreArray& getScores(); //Returns the array of score
		void loadScores(); //Load the scores from the file
	};

}

#endif