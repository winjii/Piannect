#include "StaffNotation.h"


namespace Piannect {


StaffNotation::StaffNotation(double x, double y, double width, double height)
: m_x(x)
, m_y(y)
, m_width(width)
, m_height(height) {
	m_lineDiff = height/20;
	m_centerY = y + height/2;
	double d[12] = { 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1 };
	m_noteY[m_centerKey] = m_centerY;
	for (int i = m_centerKey + 1; i < 128; i++) {
		m_noteY[i] = m_noteY[i - 1] - d[(i + 11) % 12]*m_lineDiff/2;
	}
	for (int i = m_centerKey - 1; i >= 0; i--) {
		m_noteY[i] = m_noteY[i + 1] + d[i % 12]*m_lineDiff/2;
	}
	m_appearanceX = m_x + m_width*0.9;
}

void StaffNotation::pushNote(int key) {
	m_notes.push_back(std::pair<int, double>(key, 0));
}

void StaffNotation::update() {
	for (int i = 0; i < 5; i++) {
		double g = m_centerY - m_lineDiff*(i + 1);
		double f = m_centerY + m_lineDiff*(i + 1);
		Line(m_x, g, m_x + m_width, g).draw(1.5, Palette::Black);
		Line(m_x, f, m_x + m_width, f).draw(1.5, Palette::Black);
	}
	for (auto itr = m_notes.begin(); itr != m_notes.end();) {
		int &key = itr->first;
		double &delta = itr->second;
		Vec2 pos(m_appearanceX - delta, m_noteY[key]);
		double b = m_lineDiff/2;
		Ellipse(pos, b*1.3, b).draw(Palette::Black);
		delta += 3;
		if (m_appearanceX - delta < m_x) itr = m_notes.erase(itr);
		else itr++;
	}
}


}
