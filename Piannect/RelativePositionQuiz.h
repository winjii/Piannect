#pragma once
#include "NoteFlow.h"
#include "KeyboardView.h"
#include "MidiIn.h"


namespace Piannect {


class RelativePositionQuiz : MidiIn::ITurnOnHandler, MidiIn::ITurnOffHandler {
private:

	RectF m_v;

	SP<NoteFlow> m_noteFlow;

	KeyboardView m_kv;

	SP<MidiIn> m_midiIn;

public:

	RelativePositionQuiz(double x, double y, double width, double height, const KeyType &key, SP<MidiIn> midiIn);

	RelativePositionQuiz(double x, double y, double width, double height, SP<MidiIn> midiIn);

	void update();

	// ITurnOnHandler を介して継承されました
	virtual void onTurnOn(int noteNumber) override;


	// ITurnOffHandler を介して継承されました
	virtual void onTunrOff(int noteNumber) override;

};


}