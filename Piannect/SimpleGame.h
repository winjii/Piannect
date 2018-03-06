#pragma once
#include "StaffNotation.h"
#include "KeyType.h"

namespace Piannect {


//TODO: 音符生成アルゴリズムが複雑なので別のクラスに分離
class SimpleGame : StaffNotation {
private:

	const double m_timeLimit = 3.0;

	std::deque<int> m_notes;

	double m_deadlineX;

	double m_noteInterval;

	double m_startX, m_endX;

	Transition m_noteTransition;

	int m_headNoteIndex;

	std::deque<double> m_correctTimes[128];

	double m_averageTimes[128];

	Stopwatch m_watch;

	Array<int> m_blacklist;

	const bool m_modMode;

	const bool m_usesBlackList;

	const bool m_skipMode; //TODO: これを使って場合分け

	const SP<KeyType> m_keyType;

	Texture m_sharp;

	Texture m_flat;



	double getNoteOriginX();

	void maintainBlacklist();

public:

	//keyType: nullable
	SimpleGame(double x, double y, double width, double height, SP<KeyType> keyType, bool modMode = false, bool usesBlackList = true, bool skipMode = true);

	void push(int key);

	void update() override;
};


}