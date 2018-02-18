#pragma once


namespace Piannect {


class StaffNotation {
private:

	int m_centerKey = 60;

	bool m_isBlack[12] = { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0 };

	double m_x, m_y, m_width, m_height;

	double m_lineDiff;

	double m_centerY;

	double m_noteY[128];

	double m_appearanceX;

	std::list<std::pair<int, double>> m_notes;

public:

	StaffNotation(double x, double y, double width, double height);

	int calcAccidentals(int key);

	void pushNote(int key);

	void update();
};


}