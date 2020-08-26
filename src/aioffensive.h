#ifndef DATAMODEL_AIOFFENSIVE_H
#define DATAMODEL_AIOFFENSIVE_H

#include <list>
#include "aistrategie.h"
#include "timer.h"

namespace DataModel {

	class AIOffensive : public DataModel::AIStrategie {
	private:
		static bool takeSecond;
		Utils::Timer m_decisionTimer;

	public:
		AIOffensive();

		void update(DataModel::Map& map, DataModel::Player& owner); //What do now?
	};

}

#endif