#ifndef DATAMODEL_AICRAZY_H
#define DATAMODEL_AICRAZY_H

#include <array>
#include <random>
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
		std::array<Decision, 5> m_decisions;
		Utils::Timer m_decisionTimer;
		std::mt19937 m_gen;

	public:
		AICrazy();

		void update(DataModel::Map& map, DataModel::Player& owner); //What do now?
	};

}

#endif