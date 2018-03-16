#pragma once
#include "NoteFlow.h"


namespace Piannect {


class AbsolutePositionQuiz {
private:

	NoteFlow m_noteFlow;

	const bool m_modMode;

public:

	AbsolutePositionQuiz(double x, double y, double width, double height, const KeyType &key, bool modMode = false);

	void update();

	void push(int noteNumber);
};


}