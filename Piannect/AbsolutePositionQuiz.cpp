#include "stdafx.h"
#include "AbsolutePositionQuiz.h"

namespace Piannect {


AbsolutePositionQuiz::AbsolutePositionQuiz(double x, double y, double width, double height, SP<MidiIn> midiIn, bool modMode)
: m_noteFlow(x, y, width, height*0.7, KeyType(KeyType::None),width/3)
, m_kv(x, y + height*0.7, width, height*0.3)
, m_midiIn(midiIn)
, m_modMode(modMode) {
	m_midiIn->addHandler(SP<MidiIn::ITurnOnHandler>((MidiIn::ITurnOnHandler*)this));
	m_midiIn->addHandler(SP<MidiIn::ITurnOffHandler>((MidiIn::ITurnOffHandler*)this));
}

void AbsolutePositionQuiz::update() {
	m_midiIn->update();
	m_kv.update();

	while (m_noteFlow.noteCount() < 3)
		m_noteFlow.addNote(Random(60 - 12*2, 60 + 12*3));
	m_noteFlow.update();
}

void AbsolutePositionQuiz::onTurnOn(int noteNumber) {
	int correct = [&]() {
		if (!m_modMode) return m_noteFlow.frontNote();
		noteNumber %= 12;
		return m_noteFlow.frontNote() % 12;
	}();
	if (noteNumber != correct) return;
	m_noteFlow.forward();
	m_kv.turnOn(noteNumber);
}

void AbsolutePositionQuiz::onTunrOff(int noteNumber) {
	m_kv.turnOff(noteNumber);
}


}