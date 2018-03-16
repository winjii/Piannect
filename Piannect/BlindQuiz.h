#pragma once
#include "NoteFlow.h"
#include "MidiIn.h"
#include "KeyboardView.h"


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


class BlindQuiz : MidiIn::ITurnOnHandler, MidiIn::ITurnOffHandler {
private:

	BlindFlow m_noteFlow;

	KeyboardView m_kv;

	SP<MidiIn> m_midiIn;

public:

	BlindQuiz(double x, double y, double width, double height, const KeyType &keyType, int maxSize, SP<MidiIn> midiIn);

	void update();

	// ITurnOnHandler ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void onTurnOn(int noteNumber) override;

	// ITurnOffHandler ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void onTunrOff(int noteNumber) override;
};


}