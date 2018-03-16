#include "stdafx.h"
#include "KeyboardView.h"


namespace Piannect {


void KeyboardView::setIsOn(int noteNumber, bool value) {
	noteNumber -= 36;
	if (noteNumber < 0 || 88 < noteNumber) return;
	int octave = noteNumber/12;
	int pitch = noteNumber % 12;
	m_isOn[noteNumber] = value;
}

KeyboardView::KeyboardView(double x, double y, double width, double height)
: m_x(x)
, m_y(y)
, m_width(width)
, m_height(height)
, m_isOn() {

}

void KeyboardView::turnOn(int noteNumber) {
	setIsOn(noteNumber, true);
}

void KeyboardView::turnOff(int noteNumber) {
	setIsOn(noteNumber, false);
}

void KeyboardView::update() {
	const int whiteCount = 5*7 + 1;
	double whiteWidth = m_width/whiteCount;
	constexpr int whiteKey[7] = { 0, 2, 4, 5, 7, 9, 11 };
	constexpr int blackKey[6] = { 1, 3, -1, 6, 8, 10 }; //3�ڂ͖��̍���
	for (int i = 0; i < whiteCount; i++) {
		int key = (i/7)*12 + whiteKey[i % 7];
		Color color = m_isOn[key] ? Palette::Red : ((i/7)&1 ? Color(215) : Palette::White);
		RectF(m_x + whiteWidth*i, m_y, whiteWidth, m_height).draw(color).drawFrame(1, Palette::Black);
	}
	double blackWidth = whiteWidth*0.45;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (j == 2) continue;
			int key = i*12 + blackKey[j];
			Color color = m_isOn[key] ? Palette::Red : Palette::Black;
			RectF(m_x + whiteWidth*(i*7 + j + 1) - blackWidth/2, m_y, blackWidth, m_height*0.65)
				.draw(color)
				.drawFrame(1, Palette::Black);
		}
	}
}


}