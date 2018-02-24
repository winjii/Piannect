#pragma once


namespace Piannect {


class StaffNotation {
protected:

	const int m_centerKey = 60;

	bool m_isBlack[12] = { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0 };

	bool m_isHalfStep[7] = { 0, 0, 1, 0, 0, 0, 1 };

	double m_x, m_y, m_width, m_height;

	double m_lineDiff;

	double m_centerY;

	double m_noteY[128];

	int m_bottomKey, m_topKey;

public:

	StaffNotation(double x, double y, double width, double height);

	virtual void update();
};


}