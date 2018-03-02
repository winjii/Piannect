#pragma once
#include "StaffNotation.h"

namespace Piannect {


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



	double getNoteOriginX();

	void maintainBlacklist();

public:

	SimpleGame(double x, double y, double width, double height);

	void push(int key);

	void update() override;
};


}