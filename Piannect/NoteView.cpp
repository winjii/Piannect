#include "stdafx.h"
#include "NoteView.h"


namespace Piannect {


NoteView::NoteView(double x, double y, double width, double height)
: StaffNotation(x, y, width, height)
, m_appearanceX()
, m_notes() {
	m_appearanceX = m_x + m_width*0.9;
}

void NoteView::pushNote(int key) {
	m_notes.push_front(std::pair<int, double>(key, 0));
}

void NoteView::update() {
	StaffNotation::update();

	for (auto itr = m_notes.begin(); itr != m_notes.end();) {
		int &key = itr->first;
		double &delta = itr->second;
		Vec2 pos(m_appearanceX - delta, m_noteY[key]);
		if (m_isBlack[key % 12]) {
			Circle(pos, m_lineDiff/2).draw(Palette::Black);
		}
		else {
			Circle(pos, m_lineDiff/2).draw(Palette::White).drawFrame(1.5, Palette::Black);
		}
		delta += 3;
		if (m_appearanceX - delta < m_x) itr = m_notes.erase(itr);
		else itr++;
	}
}


}