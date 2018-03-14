#pragma once
#include "NoteFlow.h"


namespace Piannect {


class BlindFlow : public NoteFlow {
private:

	int m_maxSize;

	void drawNote(int index) override {
		if ((0 < m_headNoteIndex || m_notes.size() < m_maxSize) && m_headNoteIndex <= index) return;
		NoteFlow::drawNote(index);
	}

public:

	BlindFlow(double x, double y, double width, double height, const KeyType &keyType, int maxSize)
	: NoteFlow(x, y, width, height, keyType, (width - NoteFlow::CalcDeadlinePos())/(maxSize + 1))
	, m_maxSize(maxSize) {
		
	}

	int maxSize() { return m_maxSize; }

};


class BlindQuiz {
private:

	BlindFlow m_bf;

public:

	BlindQuiz(double x, double y, double width, double height, const KeyType &keyType, int maxSize);

	void update();

	void push(int noteNumber);
};


}