#include "stdafx.h"
#include "BlindQuiz.h"


namespace Piannect {




BlindQuiz::BlindQuiz(double x, double y, double width, double height, const KeyType & keyType, int maxSize, SP<MidiIn> midiIn)
: m_noteFlow(new BlindFlow(x, y, width, height*0.7, keyType, maxSize))
, m_kv(x, y + height*0.7, width, height*0.3)
, m_midiIn(midiIn) {
	m_midiIn->addHandler(SP<MidiIn::ITurnOnHandler>((MidiIn::ITurnOnHandler*)this));
	m_midiIn->addHandler(SP<MidiIn::ITurnOffHandler>((MidiIn::ITurnOffHandler*)this));
}

void BlindQuiz::update() {
	m_midiIn->update();
	m_kv.update();

	if (MouseL.down())
		m_noteFlow = BlindFlow::Create(*m_noteFlow, KeyType::RandomKey());

	//ranges: ”¼ŠJ‹æŠÔ
	auto randomSelect = [&](const std::vector<std::pair<int, int>> &ranges) {
		std::vector<int> candidate;
		for (int i = 0; i < ranges.size(); i++) {
			for (int j = ranges[i].first; j < ranges[i].second; j++) {
				if (!m_noteFlow->keyType().isUsedKey(j)) continue;
				candidate.push_back(j);
			}
		}
		return RandomSelect(candidate);
	};

	if (m_noteFlow->frontNote() == -1) {
		using PII = std::pair<int, int>;
		int lastKey = randomSelect({PII(60 - 2*12, 60 + 3*12 + 1)});
		for (int i = 0; i < m_noteFlow->maxSize(); i++) {
			int newKey;
			PII r(std::max(60 - 2*12,  lastKey - 12), std::min(60 + 3*12 + 1, lastKey + 12 + 1));
			newKey = randomSelect({r});
			m_noteFlow->addNote(newKey);
			lastKey = newKey;
		}
		m_noteFlow->show();
	}

	m_noteFlow->update();
}

void BlindQuiz::onTurnOn(int noteNumber) {
	if (noteNumber == m_noteFlow->frontNote()) {
		m_noteFlow->forward();
		m_noteFlow->hide();
	}
	m_kv.turnOn(noteNumber);
}

void BlindQuiz::onTunrOff(int noteNumber) {
	m_kv.turnOff(noteNumber);
}

}