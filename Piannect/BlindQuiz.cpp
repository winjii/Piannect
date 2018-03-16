#include "stdafx.h"
#include "BlindQuiz.h"


namespace Piannect {




BlindQuiz::BlindQuiz(double x, double y, double width, double height, const KeyType & keyType, int maxSize)
: m_noteFlow(x, y, width, height, keyType, maxSize) {

}

void BlindQuiz::update() {
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

	if (m_noteFlow.noteCount() == 0) {
		using PII = std::pair<int, int>;
		int lastKey = randomSelect({PII(60 - 2*12, 60 + 3*12 + 1)});
		for (int i = 0; i < m_noteFlow.maxSize(); i++) {
			int newKey;
			PII r(std::max(60 - 2*12,  lastKey - 12), std::min(60 + 3*12 + 1, lastKey + 12 + 1));
			newKey = randomSelect({r});
			m_noteFlow.addNote(newKey);
			lastKey = newKey;
		}
	}

	m_noteFlow.update();
}

void BlindQuiz::push(int noteNumber) {
	if (noteNumber != m_noteFlow.frontNote()) return;
	m_noteFlow.forward();
}

}