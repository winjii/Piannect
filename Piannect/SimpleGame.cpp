#include "stdafx.h"
#include "SimpleGame.h"


namespace Piannect {


double SimpleGame::getNoteOriginX() {
	double value = m_noteTransition.value();
	double r = m_noteTransition.easeOut(Easing::Quart);
	return m_startX + (m_endX - m_startX)*r;
}

void SimpleGame::maintainBlacklist() {
	if (!m_usesBlackList || m_blacklist.size() >= 5) return;
	bool blacklisted[128] = {};
	for (int i = 0; i < (int)m_blacklist.size(); i++) {
		blacklisted[m_blacklist[i]] = true;
	}
	using pdi = std::pair<double, int>;
	std::vector<pdi> candidate;
	for (int i = 0; i < 128; i++) {
		if (!blacklisted[i] && m_averageTimes[i] > 2.0) 
			candidate.push_back(pdi(m_averageTimes[i] + Random(), i));
	}
	std::sort(candidate.begin(), candidate.end());
	while (m_blacklist.size() < 5 && candidate.size() > 0) {
		m_blacklist.push_back(candidate.back().second);
		candidate.pop_back();
	}
}

SimpleGame::SimpleGame(double x, double y, double width, double height, bool modMode, bool usesBlackList, bool skipMode)
: StaffNotation(x, y, width, height)
, m_notes()
, m_deadlineX(x + 100)
, m_noteInterval(width/3)
, m_startX()
, m_endX()
, m_noteTransition()
, m_headNoteIndex(0)
, m_correctTimes()
, m_averageTimes()
, m_watch(true)
, m_blacklist()
, m_modMode(modMode)
, m_usesBlackList(usesBlackList)
, m_skipMode(skipMode) {
	m_startX = m_deadlineX + m_noteInterval;
	m_endX = m_deadlineX + m_noteInterval;
	m_noteTransition = Transition(0s, 0s);
	for (int i = 0; i < 128; i++) {
		if (i < 60 - 12*2 || 60 + 12*3 < i) m_averageTimes[i] = 0.0;
		else m_averageTimes[i] = 1e10;
	}
	maintainBlacklist();
}

void SimpleGame::push(int key) {
	if (m_notes.size() <= m_headNoteIndex) return;
	if (m_modMode) {
		if (m_notes[m_headNoteIndex] % 12 != key % 12) return;
	}
	else {
		if (m_notes[m_headNoteIndex] != key) return;
	}
	
	key = m_notes[m_headNoteIndex];
	m_correctTimes[key].push_back(m_watch.sF());
	m_averageTimes[key] = 0.0;
	while (m_correctTimes[key].size() > 3) m_correctTimes[key].pop_front();
	for (int i = 0; i < (int)m_correctTimes[key].size(); i++) m_averageTimes[key] += m_correctTimes[key][i];
	m_averageTimes[key] /= m_correctTimes[key].size();
	if (m_averageTimes[key] < m_timeLimit && m_correctTimes[key].size() == 3) {
		auto itr = std::find(m_blacklist.begin(), m_blacklist.end(), key);
		if (itr != m_blacklist.end()) {
			m_blacklist.erase(itr);
			maintainBlacklist();
		}
	}

	m_startX = getNoteOriginX();
	m_endX = m_deadlineX - m_headNoteIndex*m_noteInterval;
	m_headNoteIndex++;
	m_noteTransition = Transition(5s, 0s);
	m_watch.restart();
}

void SimpleGame::update() {
	//ranges: ”¼ŠJ‹æŠÔ
	auto randomSelect = [&](const std::vector<std::pair<int, int>> &ranges) {
		int sum = 0;
		for (int i = 0; i < (int)ranges.size(); i++) sum += ranges[i].second - ranges[i].first;
		int rand = Random(sum - 1);
		for (int i = 0; i < (int)ranges.size(); i++) {
			if (rand < ranges[i].second - ranges[i].first) return rand + ranges[i].first;
			rand -= ranges[i].second - ranges[i].first;
		}
		return -1;
	};

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
	Line(m_deadlineX, m_y, m_deadlineX, m_y + m_height).draw(3, Palette::Black);
	for (int i = 0; ; i++) {
		double x = noteOrigin + m_noteInterval*i;
		if (m_notes.size() == i) {
			if (m_x + m_width + m_lineDiff/2 < x) break;
			int lastKey = (m_notes.size() == 0 ? 60 : m_notes.back());
			Array<int> candidate;
			for each (int var in m_blacklist) {
				if (abs(var - lastKey) < 12) continue;
				candidate.push_back(var);
			}
			if (candidate.size() == 0) {
				using pii = std::pair<int, int>;
				pii r1(60 - 2*12, std::max(60 - 2*12, lastKey + 1 - 12));
				pii r2(std::min(lastKey + 12, 60 + 3*12 + 1), 60 + 3*12 + 1);
				int newKey = randomSelect({r1, r2});
				m_notes.push_back(newKey);
			}
			else m_notes.push_back(RandomSelect(candidate));
		}
		if (i < m_headNoteIndex) {
			Circle(x, m_noteY[m_notes[i]], m_lineDiff/2).draw(Palette::Red);
		}
		else if (m_isBlack[m_notes[i] % 12]) {
			Circle(x, m_noteY[m_notes[i]], m_lineDiff/2).draw(Palette::Black);
		}
		else {
			Circle(x, m_noteY[m_notes[i]], m_lineDiff/2).draw(Palette::White);
			Circle(x, m_noteY[m_notes[i]], m_lineDiff/2).drawFrame(2, Palette::Black);
		}
		if (i == m_headNoteIndex) {
			double t = std::min(1.0, m_watch.sF()/m_timeLimit);
			//Circle(x, m_noteY[m_notes[i]], EaseIn(Easing::Cubic, 300.0, m_lineDiff/2, t)).drawFrame(1, Palette::Black);
		}
	}
}


}