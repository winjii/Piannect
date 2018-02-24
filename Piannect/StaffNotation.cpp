#include "StaffNotation.h"


namespace Piannect {


StaffNotation::StaffNotation(double x, double y, double width, double height)
: m_x(x)
, m_y(y)
, m_width(width)
, m_height(height)
, m_lineDiff()
, m_centerY()
, m_noteY() {
	m_lineDiff = height/20;
	m_centerY = y + height/2;
	//‚»‚Ì‰¹‚©‚çŸ‚Ì‰¹‚És‚­‚Ç‚Ì‚­‚ç‚¢ˆÊ’u‚ªã‚ª‚é‚©
	int d[12] = { 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2 };
	m_noteY[m_centerKey] = m_centerY;
	for (int i = m_centerKey + 1; i < 128; i++) {
		m_noteY[i] = m_noteY[i - 1] - d[(i + 11) % 12]*m_lineDiff/4;
		if (m_noteY[i] >= m_y) m_topKey = i;
	}
	for (int i = m_centerKey - 1; i >= 0; i--) {
		m_noteY[i] = m_noteY[i + 1] + d[i % 12]*m_lineDiff/4;
		if (m_noteY[i] <= m_y + m_height) m_bottomKey = i;
	}
}

void StaffNotation::update() {
	for (int i = std::max(0, m_bottomKey - 1); i <= m_topKey; i++) {
		Color color = ((i/12)&1) ? Color(215) : Palette::White;
		RectF(m_x, m_noteY[i] - m_lineDiff/2, m_width, m_lineDiff/2).draw(color);
	}

	Color halfStepColor = HSV(0, 0.1, 1);
	for (int i = 0; ; i++) {
		double y = m_centerY - i*m_lineDiff/2;
		if (y < m_y) break;
		if ((i&1) == 0)
			Line(m_x, y, m_x + m_width, y).draw(1, Palette::Gray);
		if (m_isHalfStep[i % 7]) {
			//RectF(m_x, y - m_lineDiff/2, m_width, m_lineDiff/2).draw(halfStepColor);
		}
	}
	for (int i = 1; ; i++) {
		double y = m_centerY + i*m_lineDiff/2;
		if (y > m_y + m_height) break;
		if ((i&1) == 0)
			Line(m_x, y, m_x + m_width, y).draw(1, Palette::Gray);
		if (m_isHalfStep[(7 - i % 7) % 7]) {
			//RectF(m_x, y - m_lineDiff/2, m_width, m_lineDiff/2).draw(halfStepColor);
		}
	}
	for (int i = 0; i < 5; i++) {
		double g = m_centerY - m_lineDiff*(i + 1);
		double f = m_centerY + m_lineDiff*(i + 1);
		Line(m_x, g, m_x + m_width, g).draw(4, Palette::Black);
		Line(m_x, f, m_x + m_width, f).draw(4, Palette::Black);
	}
}


}
