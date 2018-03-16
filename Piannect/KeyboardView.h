#pragma once


namespace Piannect {


class KeyboardView {
private:

	double m_x, m_y, m_width, m_height;

	bool m_isOn[88];


	void setIsOn(int noteNumber, bool value);

public:

	KeyboardView(double x, double y, double width, double height);

	void turnOn(int noteNumber);

	void turnOff(int noteNumber);

	void update();

};


}