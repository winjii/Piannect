#pragma once
#include <KeyType.h>
#include <StaffNotation.h>


namespace Piannect {


class NoteFlow : StaffNotation {
protected:

	std::deque<int> m_notes;

	double m_deadlineX;

	double m_noteInterval;

	double m_startX, m_endX;

	Transition m_noteTransition;

	int m_headNoteIndex;

	Stopwatch m_watch;

	KeyType m_keyType;

	Texture m_sharp;

	Texture m_flat;



	double getNoteOriginX();

	virtual void drawNote(int index);

public:

	static double CalcDeadlinePos();

	NoteFlow(double x, double y, double width, double height, const KeyType &keyType, double noteInterval);

	double elapsedTime();

	KeyType keyType();

	void forward();

	void update() override;

	int noteCount();

	int frontNote();

	int backNote();

	void addNote(int noteNumber);

};


}