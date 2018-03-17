#pragma once
#include "NoteFlow.h"
#include "MidiIn.h"
#include "KeyboardView.h"


namespace Piannect {


class AbsolutePositionQuiz : MidiIn::ITurnOnHandler, MidiIn::ITurnOffHandler {
private:

	const double m_timeLimit = 3.0;

	NoteFlow m_noteFlow;

	KeyboardView m_kv;

	const bool m_modMode;

	SP<MidiIn> m_midiIn;

	std::deque<double> m_correctTimes[128];

	double m_averageTimes[128];

	Array<int> m_blacklist;

	Stopwatch m_watch;


	void maintainBlacklist();

public:

	AbsolutePositionQuiz(double x, double y, double width, double height, SP<MidiIn> midiIn, bool modMode = false);

	void update();

	// ITurnOnHandler ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void onTurnOn(int noteNumber) override;

	// ITurnOffHandler ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void onTunrOff(int noteNumber) override;
};


}