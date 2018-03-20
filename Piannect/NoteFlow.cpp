#include "stdafx.h"
#include "NoteFlow.h"

namespace Piannect {


double NoteFlow::getNoteOriginX() {
	double value = m_noteTransition.value();
	double r = m_noteTransition.easeOut(Easing::Quart);
	return m_startX + (m_endX - m_startX)*r;
}

void NoteFlow::drawNote(int index) {
	double x = getNoteOriginX() + m_noteInterval*index;
	int noteAsPos = m_keyType.noteAsPosition(m_notes[index]);
	if (index < m_headNoteIndex) {
		Circle(x, m_noteY[noteAsPos], m_lineDiff/2).draw(Palette::Red);
	}
	else if (m_isBlack[noteAsPos % 12]) {
		Circle(x, m_noteY[noteAsPos], m_lineDiff/2).draw(Palette::Black);
	}
	else {
		Circle(x, m_noteY[noteAsPos], m_lineDiff/2).draw(Palette::White);
		Circle(x, m_noteY[noteAsPos], m_lineDiff/2).drawFrame(2, Palette::Black);
	}
}

double NoteFlow::CalcDeadlinePos() {
	return 300;
}

SP<NoteFlow> NoteFlow::Create(const NoteFlow &base, const KeyType & keyType) {
	return SP<NoteFlow>(new NoteFlow(base.m_x, base.m_y, base.m_width, base.m_height, keyType, base.m_noteInterval));
}

NoteFlow::NoteFlow(double x, double y, double width, double height, const KeyType &keyType, double noteInterval)
	: StaffNotation(x, y, width, height)
	, m_notes()
	, m_deadlineX(x + CalcDeadlinePos())
	, m_noteInterval(noteInterval)
	, m_startX()
	, m_endX()
	, m_noteTransition()
	, m_headNoteIndex(0)
	, m_watch(true)
	, m_keyType(keyType)
	, m_sharp(U"sharp.png")
	, m_flat(U"flat.png")
	, m_lastNote(-1) {

	m_startX = m_deadlineX + m_noteInterval;
	m_endX = m_deadlineX + m_noteInterval;
	m_noteTransition = Transition(0s, 0s);
}

void NoteFlow::forward() {
	if (m_notes.size() <= m_headNoteIndex) return;
	m_startX = getNoteOriginX();
	m_endX = m_deadlineX - m_headNoteIndex*m_noteInterval;
	m_headNoteIndex++;
	m_noteTransition = Transition(5s, 0s);
	m_watch.restart();
}

void NoteFlow::update() {
	StaffNotation::update();
	m_noteTransition.update(true);
	double noteOrigin = getNoteOriginX();
	while (noteOrigin - m_lineDiff/2 < m_deadlineX) {
		m_notes.pop_front();
		m_headNoteIndex--;
		noteOrigin += m_noteInterval;
		m_startX += m_noteInterval;
		m_endX += m_noteInterval;
	}

	{
		bool isSharp = m_keyType.isSharp();
		Texture texture = isSharp ? m_sharp : m_flat;
		Vec2 center = isSharp ? Vec2(735, 755) : Vec2(750, 897);
		double scale = (isSharp ? 0.003 : 0.0038)*m_lineDiff;
		center *= scale;
		auto drawSignatures = [&](const std::vector<int> &signatures) {
			double x = m_x + 50;
			for each (int s in signatures) {
				texture.scaled(scale).draw(Vec2(x, m_noteY[s]) - center);
				x += m_lineDiff*0.9;
			}
		};
		drawSignatures(m_keyType.higherKeySignatures());
		drawSignatures(m_keyType.lowerKeySignatures());
	}
	Line(m_deadlineX, m_y, m_deadlineX, m_y + m_height).draw(3, Palette::Black);

	for (int i = 0; i < (int)m_notes.size(); i++) drawNote(i);
}

int NoteFlow::noteCount() {
	return m_notes.size();
}

int NoteFlow::frontNote() {
	if (m_notes.size() <= m_headNoteIndex) return -1;
	return m_notes[m_headNoteIndex];
}

int NoteFlow::lastNote() {
	return m_lastNote;
}

void NoteFlow::addNote(int noteNumber) {
	m_notes.push_back(noteNumber);
	m_lastNote = noteNumber;
}

double NoteFlow::elapsedTime() {
	return m_watch.sF();
}

KeyType NoteFlow::keyType() {
	return m_keyType;
}


}