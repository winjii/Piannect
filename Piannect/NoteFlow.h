#pragma once
#include <KeyType.h>
#include <StaffNotation.h>


namespace Piannect {


class NoteFlow : public StaffNotation {
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

	int m_lastNote;



	double getNoteOriginX();

	virtual void drawNote(int index);

public:

	static double CalcDeadlinePos();

	static SP<NoteFlow> Create(const NoteFlow &base, const KeyType &keyType);

	NoteFlow(double x, double y, double width, double height, const KeyType &keyType, double noteInterval);

	double elapsedTime();

	KeyType keyType();

	void forward();

	void update() override;

	int noteCount();

	//Ç‹Çæè¡Ç≥ÇÍÇƒÇ¢Ç»Ç¢âπïÑÇÃÇ§ÇøêÊì™ÇÃÇ‡ÇÃ
	int frontNote();

	//ç≈å„Ç…Ç†ÇÈ or ç≈å„Ç…Ç†Ç¡ÇΩâπïÑ
	int lastNote();

	void addNote(int noteNumber);

};


}