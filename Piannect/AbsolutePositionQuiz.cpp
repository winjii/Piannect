#include "stdafx.h"
#include "AbsolutePositionQuiz.h"

namespace Piannect {

void AbsolutePositionQuiz::maintainBlacklist() {
	if (m_blacklist.size() >= 5) return;
	bool blacklisted[128] = {};
	for (int i = 0; i < (int)m_blacklist.size(); i++) {
		blacklisted[m_blacklist[i]] = true;
	}
	using pdi = std::pair<double, int>;
	std::vector<pdi> candidate;
	for (int i = 0; i < 128; i++) {
		if (!m_noteFlow.keyType().isUsedKey(i)) continue;
		if (!blacklisted[i] && m_averageTimes[i] > 2.0) 
			candidate.push_back(pdi(m_averageTimes[i] + Random(), i));
	}
	std::sort(candidate.begin(), candidate.end());
	while (m_blacklist.size() < 5 && candidate.size() > 0) {
		m_blacklist.push_back(candidate.back().second);
		candidate.pop_back();
	}
}

AbsolutePositionQuiz::AbsolutePositionQuiz(double x, double y, double width, double height, SP<MidiIn> midiIn, bool modMode)
: m_noteFlow(x, y, width, height*0.7, KeyType(KeyType::None),width/3)
, m_kv(x, y + height*0.7, width, height*0.3)
, m_midiIn(midiIn)
, m_modMode(modMode)
, m_correctTimes()
, m_averageTimes()
, m_blacklist()
, m_watch() {
	m_midiIn->addHandler(SP<MidiIn::ITurnOnHandler>((MidiIn::ITurnOnHandler*)this));
	m_midiIn->addHandler(SP<MidiIn::ITurnOffHandler>((MidiIn::ITurnOffHandler*)this));
	for (int i = 0; i < 128; i++) {
		if (i < 60 - 12*2 || 60 + 12*3 < i) m_averageTimes[i] = 0.0;
		else m_averageTimes[i] = 1e10;
	}
	maintainBlacklist();
	m_watch.start();
}

void AbsolutePositionQuiz::update() {
	m_midiIn->update();
	m_kv.update();

	//ranges: ”¼ŠJ‹æŠÔ
	auto randomSelect = [&](const std::vector<std::pair<int, int>> &ranges) {
		std::vector<int> candidate;
		for (int i = 0; i < ranges.size(); i++) {
			for (int j = ranges[i].first; j < ranges[i].second; j++) {
				if (!m_noteFlow.keyType().isUsedKey(j)) continue;
				candidate.push_back(j);
			}
		}
		return RandomSelect(candidate);
	};

	while (m_noteFlow.noteCount() < 3) {
		int lastNote = m_noteFlow.frontNote();
		if (lastNote == -1) lastNote = 60;
		std::vector<int> candidate;
		for each (int var in m_blacklist) {
			if (abs(var - lastNote) < 12) continue;
			candidate.push_back(var);
		}
		if (candidate.size() == 0) {
			using PII = std::pair<int, int>;
			int newNote;
			PII r1(60 - 2*12, std::max(60 - 2*12, lastNote + 1 - 12));
			PII r2(std::min(lastNote + 12, 60 + 3*12 + 1), 60 + 3*12 + 1);
			m_noteFlow.addNote(randomSelect({r1, r2}));
		}
		else m_noteFlow.addNote(RandomSelect(candidate));
	}
	m_noteFlow.update();
}

void AbsolutePositionQuiz::onTurnOn(int noteNumber) {
	m_kv.turnOn(noteNumber);
	int correct = [&]() {
		if (!m_modMode) return m_noteFlow.frontNote();
		noteNumber %= 12;
		return m_noteFlow.frontNote() % 12;
	}();
	if (noteNumber != correct) return;
	correct = m_noteFlow.frontNote();
	m_noteFlow.forward();

	m_correctTimes[correct].push_back(m_watch.sF());
	m_averageTimes[correct] = 0.0;
	while (m_correctTimes[correct].size() > 3) m_correctTimes[correct].pop_front();
	for (int i = 0; i < (int)m_correctTimes[correct].size(); i++) m_averageTimes[correct] += m_correctTimes[correct][i];
	m_averageTimes[correct] /= m_correctTimes[correct].size();
	if (m_averageTimes[correct] < m_timeLimit && m_correctTimes[correct].size() == 3) {
		auto itr = std::find(m_blacklist.begin(), m_blacklist.end(), correct);
		if (itr != m_blacklist.end()) {
			m_blacklist.erase(itr);
			maintainBlacklist();
		}
	}
	m_watch.restart();
}

void AbsolutePositionQuiz::onTunrOff(int noteNumber) {
	m_kv.turnOff(noteNumber);
}


}