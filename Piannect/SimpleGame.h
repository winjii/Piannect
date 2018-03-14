#pragma once
#include "StaffNotation.h"
#include "KeyType.h"

namespace Piannect {

/*
//TODO: 音符生成アルゴリズムが複雑なので別のクラスに分離
class SimpleGame : StaffNotation {
private:

	const double m_timeLimit = 3.0;

	std::deque<double> m_correctTimes[128];

	double m_averageTimes[128];

	Array<int> m_blacklist;

	const bool m_modMode;

	const bool m_usesBlackList;

	const bool m_skipMode; //TODO: これを使って場合分け

	const bool m_blindMode;



	void maintainBlacklist();

public:

	//keyType: nullable
	SimpleGame(double x, double y, double width, double height, SP<KeyType> keyType, bool modMode = false, bool usesBlackList = true, bool skipMode = true, bool blindMode = false);

	void push(int key);

	void update() override;
};
*/


}