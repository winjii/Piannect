#include "stdafx.h"
#include "RelativePositionQuiz.h"


namespace Piannect {


RelativePositionQuiz::RelativePositionQuiz(double x, double y, double width, double height, const KeyType &key, SP<MidiIn> midiIn) 
: m_noteFlow(x, y, width, height*0.7, key, width/15)
, m_kv(x, y + height*0.7, width, height*0.3)
, m_midiIn(midiIn) {
	m_midiIn->addHandler(SP<MidiIn::ITurnOnHandler>((MidiIn::ITurnOnHandler*)this));
	m_midiIn->addHandler(SP<MidiIn::ITurnOffHandler>((MidiIn::ITurnOffHandler*)this));
}

void RelativePositionQuiz::update() {
	m_midiIn->update();
	m_kv.update();

	using PII = std::pair<int, int>;
	auto randomSelect = [&](const std::vector<PII> &ranges) {
		std::vector<int> candidate;
		for (int i = 0; i < ranges.size(); i++) {
			for (int j = ranges[i].first; j < ranges[i].second; j++) {
				if (!m_noteFlow.keyType().isUsedKey(j)) continue;
				candidate.push_back(j);
			}
		}
		return RandomSelect(candidate);
	};
	while (m_noteFlow.noteCount() < 15) {
		int lastKey = m_noteFlow.backNote();
		if (lastKey == -1) lastKey = 60;
		PII r(std::max(60 - 2*12, lastKey - 12), std::min(60 + 3*12 + 1, lastKey + 12 + 1));
		m_noteFlow.addNote(randomSelect({r}));
	}
	m_noteFlow.update();
}

void RelativePositionQuiz::onTurnOn(int noteNumber) {
	if (noteNumber == m_noteFlow.frontNote())
		m_noteFlow.forward();
	m_kv.turnOn(noteNumber);
}

void RelativePositionQuiz::onTunrOff(int noteNumber) {
	m_kv.turnOff(noteNumber);
}


}