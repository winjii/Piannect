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
		if (m_keyType && !m_keyType->isUsedKey(i)) continue;
		if (!blacklisted[i] && m_averageTimes[i] > 2.0) 
			candidate.push_back(pdi(m_averageTimes[i] + Random(), i));
	}
	std::sort(candidate.begin(), candidate.end());
	while (m_blacklist.size() < 5 && candidate.size() > 0) {
		m_blacklist.push_back(candidate.back().second);
		candidate.pop_back();
	}
}

SimpleGame::SimpleGame(double x, double y, double width, double height, SP<KeyType> keyType, bool modMode, bool usesBlackList, bool skipMode)
: StaffNotation(x, y, width, height)
, m_notes()
, m_deadlineX(x + 300)
, m_noteInterval(skipMode ? width/3 : width/10)
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
, m_skipMode(skipMode)
, m_keyType(keyType)
, m_sharp(U"sharp.png")
, m_flat(U"flat.png") {

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
		std::vector<int> candidate;
		for (int i = 0; i < ranges.size(); i++) {
			for (int j = ranges[i].first; j < ranges[i].second; j++) {
				if (m_keyType && !m_keyType->isUsedKey(j)) continue;
				candidate.push_back(j);
			}
		}
		return RandomSelect(candidate);
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

	{
		bool isSharp = m_keyType->isSharp();
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
		drawSignatures(m_keyType->higherKeySignatures());
		drawSignatures(m_keyType->lowerKeySignatures());
	}
	Line(m_deadlineX, m_y, m_deadlineX, m_y + m_height).draw(3, Palette::Black);

	for (int i = 0; ; i++) {
		double x = noteOrigin + m_noteInterval*i;
		if (m_notes.size() == i) {
			if (m_x + m_width + m_lineDiff/2 < x) break;
			int lastKey = (m_notes.size() == 0 ? 60 : m_notes.back());
			std::vector<int> candidate;
			for each (int var in m_blacklist) {
				if (m_skipMode && abs(var - lastKey) < 12) continue;
				if (!m_skipMode && abs(var - lastKey) > 12) continue;
				candidate.push_back(var);
			}
			if (candidate.size() == 0) {
				using PII = std::pair<int, int>;
				int newKey;
				if (m_skipMode) {
					PII r1(60 - 2*12, std::max(60 - 2*12, lastKey + 1 - 12));
					PII r2(std::min(lastKey + 12, 60 + 3*12 + 1), 60 + 3*12 + 1);
					newKey = randomSelect({r1, r2});
				}
				else {
					PII r(std::max(60 - 2*12, lastKey - 12), std::min(60 + 3*12 + 1, lastKey + 12 + 1));
					newKey = randomSelect({r});
				}
				m_notes.push_back(newKey);
			}
			else m_notes.push_back(RandomSelect(candidate));
		}

		int keyAsPos = m_notes[i];
		if (m_keyType) keyAsPos = m_keyType->keyAsPosition(keyAsPos);
		if (i < m_headNoteIndex) {
			Circle(x, m_noteY[keyAsPos], m_lineDiff/2).draw(Palette::Red);
		}
		else if (m_isBlack[keyAsPos % 12]) {
			Circle(x, m_noteY[keyAsPos], m_lineDiff/2).draw(Palette::Black);
		}
		else {
			Circle(x, m_noteY[keyAsPos], m_lineDiff/2).draw(Palette::White);
			Circle(x, m_noteY[keyAsPos], m_lineDiff/2).drawFrame(2, Palette::Black);
		}
		if (i == m_headNoteIndex) {
			double t = std::min(1.0, m_watch.sF()/m_timeLimit);
			//Circle(x, m_noteY[m_notes[i]], EaseIn(Easing::Cubic, 300.0, m_lineDiff/2, t)).drawFrame(1, Palette::Black);
		}
	}
}


}