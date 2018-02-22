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
	//���̉����玟�̉��ɍs�����ǂ̂��炢�ʒu���オ�邩
	int d[12] = { 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2 };
	m_noteY[m_centerKey] = m_centerY;
	for (int i = m_centerKey + 1; i < 128; i++) {
		m_noteY[i] = m_noteY[i - 1] - d[(i + 11) % 12]*m_lineDiff/4;
	}
	for (int i = m_centerKey - 1; i >= 0; i--) {
		m_noteY[i] = m_noteY[i + 1] + d[i % 12]*m_lineDiff/4;
	}
}


}
