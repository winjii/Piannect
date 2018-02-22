#pragma once
#include "StaffNotation.h"

namespace Piannect {


class NoteView : StaffNotation {
private:

	double m_appearanceX;

	std::list<std::pair<int, double>> m_notes;

public:

	NoteView(double x, double y, double width, double height);

	void pushNote(int key);

	void update();
};


}