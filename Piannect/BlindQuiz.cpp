#include "stdafx.h"
#include "BlindQuiz.h"


namespace Piannect {




BlindQuiz::BlindQuiz(double x, double y, double width, double height, const KeyType & keyType, int maxSize)
: m_bf(x, y, width, height, keyType, maxSize) {

}

void BlindQuiz::update() {
	//ranges: ”¼ŠJ‹æŠÔ
	auto randomSelect = [&](const std::vector<std::pair<int, int>> &ranges) {
		std::vector<int> candidate;
		for (int i = 0; i < ranges.size(); i++) {
			for (int j = ranges[i].first; j < ranges[i].second; j++) {
				if (!m_bf.keyType().isUsedKey(j)) continue;
				candidate.push_back(j);
			}
		}
		return RandomSelect(candidate);
	};

	if (m_bf.noteCount() == 0) {
		using PII = std::pair<int, int>;
		int lastKey = randomSelect({PII(60 - 2*12, 60 + 3*12 + 1)});
		for (int i = 0; i < m_bf.maxSize(); i++) {
			int newKey;
			PII r(std::max(60 - 2*12,  lastKey - 12), std::min(60 + 3*12 + 1, lastKey + 12 + 1));
			newKey = randomSelect({r});
			m_bf.addNote(newKey);
			lastKey = newKey;
		}
	}

	m_bf.update();
}

void BlindQuiz::push(int noteNumber) {
	if (noteNumber != m_bf.note(0)) return;
	m_bf.forward();
}

}