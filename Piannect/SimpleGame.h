#pragma once
#include "StaffNotation.h"

namespace Piannect {


class SimpleGame : StaffNotation {
private:

	const int m_nextRange = 8;

	std::deque<int> m_notes;

	double m_deadlineX;

	double m_noteInterval;

	double m_startX, m_endX;

	Transition m_noteTransition;

	int m_headNoteIndex;


	double getNoteOriginX();

public:

	SimpleGame(double x, double y, double width, double height);

	void push(int key);

	void update() override;
};


}