#include "stdafx.h"
#include "SimpleGame.h"


namespace Piannect {


double SimpleGame::getNoteOriginX() {
	double value = m_noteTransition.value();
	double r = m_noteTransition.easeOut(Easing::Quart);
	return m_startX + (m_endX - m_startX)*r;
}

SimpleGame::SimpleGame(double x, double y, double width, double height)
: StaffNotation(x, y, width, height)
, m_notes()
, m_deadlineX(x + 100)
, m_noteInterval(100)
, m_startX()
, m_endX()
, m_noteTransition()
, m_headNoteIndex(0) {
	m_startX = m_deadlineX + m_noteInterval;
	m_endX = m_deadlineX + m_noteInterval;
	m_noteTransition = Transition(0s, 0s);
}

void SimpleGame::push(int key) {
	if (m_notes[m_headNoteIndex] != key) return;
	m_startX = getNoteOriginX();
	m_endX = m_deadlineX - m_headNoteIndex*m_noteInterval;
	m_headNoteIndex++;
	m_noteTransition = Transition(5s, 0s);
}

void SimpleGame::update() {
	StaffNotation::update();
	m_noteTransition.update(true);
	double noteOrigin = getNoteOriginX();
	while (noteOrigin - m_lineDiff/2 < m_deadlineX) {
		m_notes.pop_front();
		m_headNoteIndex--;
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
		if (i < m_headNoteIndex) {
			Circle(x, m_noteY[m_notes[i]], m_lineDiff/2).draw(Palette::Red);
		}
		else if (m_isBlack[m_notes[i] % 12]) {
			Circle(x, m_noteY[m_notes[i]], m_lineDiff/2).draw(Palette::Black);
		}
		else {
			Circle(x, m_noteY[m_notes[i]], m_lineDiff/2).draw(Palette::White);
			Circle(x, m_noteY[m_notes[i]], m_lineDiff/2).drawFrame(2, Palette::Black);
		}
	}
}


}