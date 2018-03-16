#pragma once
#include "NoteFlow.h"
#include "MidiIn.h"
#include "KeyboardView.h"


namespace Piannect {


class AbsolutePositionQuiz : MidiIn::ITurnOnHandler, MidiIn::ITurnOffHandler {
private:

	NoteFlow m_noteFlow;

	KeyboardView m_kv;

	const bool m_modMode;

	SP<MidiIn> m_midiIn;

public:

	AbsolutePositionQuiz(double x, double y, double width, double height, SP<MidiIn> midiIn, bool modMode = false);

	void update();

	// ITurnOnHandler ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void onTurnOn(int noteNumber) override;

	// ITurnOffHandler ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void onTunrOff(int noteNumber) override;
};


}