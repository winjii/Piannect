#include "stdafx.h"
#include "SimpleGame.h"


namespace Piannect {


double SimpleGame::getNoteOriginX() {
	return m_startX + (m_endX - m_startX)*m_noteTransition.easeOut(Easing::Quart);
}

SimpleGame::SimpleGame(double x, double y, double width, double height)
: StaffNotation(x, y, width, height)
, m_notes()
, m_deadlineX(x + 30)
, m_noteInterval(20)
, m_startX()
, m_endX()
, m_noteTransition() {
	m_startX = m_deadlineX + m_noteInterval;
	m_endX = m_deadlineX + m_noteInterval;
	m_noteTransition = Transition(0s, 0s);
}

void SimpleGame::push(int key) {
	if (m_notes.front() != key) return;
	m_notes.pop_front();
	m_noteTransition = Transition(0.5s, 0s);
	m_startX = getNoteOriginX();
	m_endX = m_deadlineX + m_noteInterval;
}

void SimpleGame::update() {
	StaffNotation::update();
	m_noteTransition.update(true);
	double noteOrigin = getNoteOriginX();
	if (noteOrigin < m_deadlineX + 1e-10) {
		m_notes.pop_front();
		noteOrigin += m_noteInterval;
		m_startX += m_noteInterval;
		m_endX += m_noteInterval;
	}
	Line(m_deadlineX, m_y, m_deadlineX, m_y + m_height).draw(3, Palette::Black);
	for (int i = 0; ; i++) {
		double x = noteOrigin + m_noteInterval*i;
		if (m_notes.size() == i) {
			if (m_x + m_width + m_lineDiff/2 < x) break;
			int lastKey = (m_notes.size() == 0 ? 60 : m_notes.back());
			int newKey = lastKey - m_nextRange + Random(m_nextRange*2);
			newKey = std::max(60 - 12*2, std::min(newKey, 60 + 3*21 + 1));
			m_notes.push_back(newKey);
		}
		Circle(x, m_noteY[m_notes[i]], m_lineDiff/2).draw(Palette::Black);
	}
}


}