#include "stdafx.h"
#include "AbsolutePositionQuiz.h"

namespace Piannect {


AbsolutePositionQuiz::AbsolutePositionQuiz(double x, double y, double width, double height, const KeyType & key, bool modMode)
: m_noteFlow(x, y, width, height, key, width/3)
, m_modMode(modMode) {
	
}

void AbsolutePositionQuiz::update() {
	while (m_noteFlow.noteCount() < 3)
		m_noteFlow.addNote(Random(60 - 12*2, 60 + 12*3));
	m_noteFlow.update();
}

void AbsolutePositionQuiz::push(int noteNumber) {
	int correct = [&]() {
		if (!m_modMode) return m_noteFlow.frontNote();
		noteNumber %= 12;
		return m_noteFlow.frontNote() % 12;
	}();
	if (noteNumber != correct) return;
	m_noteFlow.forward();
}


}