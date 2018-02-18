#include "StaffNotation.h"


namespace Piannect {


StaffNotation::StaffNotation(double x, double y, double width, double height)
: m_x(x)
, m_y(y)
, m_width(width)
, m_height(height)
, m_lineDiff()
, m_centerY()
, m_noteY()
, m_appearanceX()
, m_notes() {
	m_lineDiff = height/20;
	m_centerY = y + height/2;
	//ÇªÇÃâπÇ©ÇÁéüÇÃâπÇ…çsÇ≠éûÇ«ÇÃÇ≠ÇÁÇ¢à íuÇ™è„Ç™ÇÈÇ©
	int d[12] = { 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2 };
	m_noteY[m_centerKey] = m_centerY;
	for (int i = m_centerKey + 1; i < 128; i++) {
		m_noteY[i] = m_noteY[i - 1] - d[(i + 11) % 12]*m_lineDiff/4;
	}
	for (int i = m_centerKey - 1; i >= 0; i--) {
		m_noteY[i] = m_noteY[i + 1] + d[i % 12]*m_lineDiff/4;
	}
	m_appearanceX = m_x + m_width*0.9;
}

void StaffNotation::pushNote(int key) {
	m_notes.push_front(std::pair<int, double>(key, 0));
}

void StaffNotation::update() {
	for (int i = 0; i < 5; i++) {
		double g = m_centerY - m_lineDiff*(i + 1);
		double f = m_centerY + m_lineDiff*(i + 1);
		Line(m_x, g, m_x + m_width, g).draw(1.1, Palette::Black);
		Line(m_x, f, m_x + m_width, f).draw(1.1, Palette::Black);
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
