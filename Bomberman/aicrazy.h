#ifndef DATAMODEL_AICRAZY_H
#define DATAMODEL_AICRAZY_H

#include <boost/array.hpp>
#include <boost/random.hpp>
#include "aistrategie.h"
#include "timer.h"

namespace DataModel {

	class AICrazy : public AIStrategie {
	private:
		enum Decision {
			MoveUp,
			MoveDown,
			MoveLeft,
			MoveRight,
			DropBomb
		};

		Decision m_currentDecision;
		boost::array<Decision, 5> m_decisions;
		Utils::Timer m_decisionTimer;
		boost::mt19937 m_gen;

	public:
		AICrazy();

		void update(DataModel::Map& map, DataModel::Player& owner); //What do now?
	};

}

#endif