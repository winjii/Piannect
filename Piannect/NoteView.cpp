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
	Color halfStepColor = HSV(0, 0.1, 1);
	for (int i = 0; ; i++) {
		double y = m_centerY - i*m_lineDiff/2;
		if (y < m_y) break;
		//if ((i&1) == 0)
		Line(m_x, y, m_x + m_width, y).draw(0.3, Palette::Gray);
		if (m_isHalfStep[i % 7]) {
			RectF(m_x, y - m_lineDiff/2, m_width, m_lineDiff/2).draw(halfStepColor);
		}
	}
	for (int i = 1; ; i++) {
		double y = m_centerY + i*m_lineDiff/2;
		if (y > m_y + m_height) break;
		//if ((i&1) == 0)
		Line(m_x, y, m_x + m_width, y).draw(0.3, Palette::Gray);
		if (m_isHalfStep[(7 - i % 7) % 7]) {
			RectF(m_x, y - m_lineDiff/2, m_width, m_lineDiff/2).draw(halfStepColor);
		}
	}
	for (int i = 0; i < 5; i++) {
		double g = m_centerY - m_lineDiff*(i + 1);
		double f = m_centerY + m_lineDiff*(i + 1);
		Line(m_x, g, m_x + m_width, g).draw(3.5, Palette::Black);
		Line(m_x, f, m_x + m_width, f).draw(3.5, Palette::Black);
	}
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