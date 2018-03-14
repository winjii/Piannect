#include "KeyType.h"


namespace Piannect {


KeyType KeyType::RandomKey() {
	return KeyType((Type)Random((int)KeyType::Cf, (int)KeyType::B_m));
}

KeyType::KeyType(Type type)
: m_type(type)
, m_noteAsPosition()
, m_isUsedKey()
, m_higherKeySignatures()
, m_lowerKeySignatures()
, m_isSharp() {

	if (type == KeyType::None) {
		m_isSharp = false;
		for (int i = 0; i < 12; i++) {
			m_isUsedKey[i] = true;
			m_noteAsPosition[i] = i;
		}
		return;
	}

	using P = std::pair<int, int>;

	auto setIsUsedKey = [&](const std::array<const int, 7> &indices) {
		for (int i = 0; i < 7; i++) m_isUsedKey[indices[i]] = true;
	};
	auto setKeyAsPosition = [&](const std::array<const P, 7> &initList) {
		for (int i = 0; i < 7; i++) m_noteAsPosition[initList[i].first] = initList[i].second;
	};

	std::array<int, 7> usedKeys; //基準の音から順に
	std::array<int, 7> signatures; //基準の音から順に。フラットが-1シャープが1
	int signatureCount;
	switch (type) {
	case KeyType::Cf:
		usedKeys = { 11, 1, 3, 4, 6, 8, 10 };
		signatures = { -1, -1, -1, -1, -1, -1, -1 };
		m_isSharp = false;
		signatureCount = 7;
		break;
	case KeyType::C:
		usedKeys = { 0, 2, 4, 5, 7, 9, 11 };
		signatures = { 0, 0, 0, 0, 0, 0, 0 };
		signatureCount = 0;
		break;
	case KeyType::Cs:
		usedKeys = { 1, 3, 5, 6, 8, 10, 0 };
		signatures = { 1, 1, 1, 1, 1, 1, 1 };
		m_isSharp = true;
		signatureCount = 7;
		break;
	case KeyType::Df:
		usedKeys = { 1, 3, 5, 6, 8, 10, 0 };
		signatures = { -1, -1, 0, -1, -1, -1, 0 };
		m_isSharp = false;
		signatureCount = 5;
		break;
	case KeyType::D:
		usedKeys = { 2, 4, 6, 7, 9, 11, 1 };
		signatures = { 0, 0, 1, 0, 0, 0, 1 };
		m_isSharp = true;
		signatureCount = 2;
		break;
	case KeyType::Ef:
		usedKeys = { 3, 5, 7, 8, 10, 0, 2 };
		signatures = { -1, 0, 0, -1, -1, 0, 0 };
		m_isSharp = false;
		signatureCount = 3;
		break;
	case KeyType::E:
		usedKeys = { 4, 6, 8, 9, 11, 1, 3 };
		signatures = { 0, 1, 1, 0, 0, 1, 1 };
		m_isSharp = true;
		signatureCount = 4;
		break;
	case KeyType::F:
		usedKeys = { 5, 7, 9, 10, 0, 2, 4 };
		signatures = { 0, 0, 0, -1, 0, 0, 0 };
		m_isSharp = false;
		signatureCount = 1;
		break;
	case KeyType::Fs:
		usedKeys = { 6, 8, 10, 11, 1, 3, 5 };
		signatures = { 1, 1, 1, 0, 1, 1, 1 };
		m_isSharp = true;
		signatureCount = 6;
		break;
	case KeyType::Gf:
		usedKeys = { 6, 8, 10, 11, 1, 3, 5 };
		signatures = { -1, -1, -1, -1, -1, -1, 0 };
		m_isSharp = false;
		signatureCount = 6;
		break;
	case KeyType::G:
		usedKeys = {7, 9, 11, 0, 2, 4, 6};
		signatures = { 0, 0, 0, 0, 0, 0, 1 };
		m_isSharp = true;
		signatureCount = 1;
		break;
	case KeyType::Af:
		usedKeys = { 8, 10, 0, 1, 3, 5, 7 };
		signatures = { -1, -1, 0, -1, -1, 0, 0 };
		m_isSharp = false;
		signatureCount = 4;
		break;
	case KeyType::A:
		usedKeys = { 9, 11, 1, 2, 4, 6, 8 };
		signatures = { 0, 0, 1, 0, 0, 1, 1 };
		m_isSharp = true;
		signatureCount = 3;
		break;
	case KeyType::Bf:
		usedKeys = { 10, 0, 2, 3, 5, 7, 9 };
		signatures = { -1, 0, 0, -1, 0, 0, 0 };
		m_isSharp = false;
		signatureCount = 2;
		break;
	case KeyType::B:
		usedKeys = { 11, 1, 3, 4, 6, 8, 10 };
		signatures = { 0, 1, 1, 0, 1, 1, 1 };
		m_isSharp = true;
		signatureCount = 5;
		break;
	case Piannect::KeyType::C_m:
		usedKeys = { 0, 2, 3, 5, 7, 8, 10 };
		signatures = { 0, 0, -1, 0, 0, -1, -1 };
		m_isSharp = false;
		signatureCount = 3;
		break;
	case Piannect::KeyType::Cs_m:
		usedKeys = { 1, 3, 4, 6, 8, 9, 11 };
		signatures = { 1, 1, 0, 1, 1, 0, 0 };
		m_isSharp = true;
		signatureCount = 4;
		break;
	case Piannect::KeyType::D_m:
		usedKeys = { 2, 4, 5, 7, 9, 10, 0 };
		signatures = { 0, 0, 0, 0, 0, -1, 0 };
		m_isSharp = false;
		signatureCount = 1;
		break;
	case Piannect::KeyType::Ds_m:
		usedKeys = { 3, 5, 6, 8, 10, 11, 1 };
		signatures = { 1, 1, 1, 1, 1, 0, 1 };
		m_isSharp = true;
		signatureCount = 6;
		break;
	case Piannect::KeyType::Ef_m:
		usedKeys = { 3, 5, 6, 8, 10, 11, 1 };
		signatures = { -1, 0, -1, -1, -1, -1, -1 };
		m_isSharp = false;
		signatureCount = 6;
		break;
	case Piannect::KeyType::E_m:
		usedKeys = { 4, 6, 7, 9, 11, 0, 2 };
		signatures = { 0, 1, 0, 0, 0, 0, 0 };
		m_isSharp = true;
		signatureCount = 1;
		break;
	case Piannect::KeyType::F_m:
		usedKeys = { 5, 7, 8, 10, 0, 1, 3 };
		signatures = { 0, 0, -1, -1, 0, -1, -1 };
		m_isSharp = false;
		signatureCount = 4;
		break;
	case Piannect::KeyType::Fs_m:
		usedKeys = { 6, 8, 9, 11, 1, 2, 4 };
		signatures = { 1, 1, 0, 0, 1, 0, 0 };
		m_isSharp = true;
		signatureCount = 3;
		break;
	case Piannect::KeyType::G_m:
		usedKeys = { 7, 9, 10, 0, 2, 3, 5 };
		signatures = { 0, 0, -1, 0, 0, -1, 0 };
		m_isSharp = false;
		signatureCount = 2;
		break;
	case Piannect::KeyType::Gs_m:
		usedKeys = { 8, 10, 11, 1, 3, 4, 6 };
		signatures = { 1, 1, 0, 1, 1, 0, 1 };
		m_isSharp = true;
		signatureCount = 5;
		break;
	case Piannect::KeyType::Af_m:
		usedKeys = { 8, 10, 11, 1, 3, 4, 6 };
		signatures = { -1, -1, -1, -1, -1, -1, -1 };
		m_isSharp = false;
		signatureCount = 7;
		break;
	case Piannect::KeyType::A_m:
		usedKeys = { 9, 11, 0, 2, 4, 5, 7 };
		signatures = { 0, 0, 0, 0, 0, 0, 0 };
		m_isSharp = false;
		signatureCount = 0;
		break;
	case Piannect::KeyType::As_m:
		usedKeys = { 10, 0, 1, 3, 5, 6, 8 };
		signatures = { 1, 1, 1, 1, 1, 1, 1 };
		m_isSharp = true;
		signatureCount = 7;
		break;
	case Piannect::KeyType::Bf_m:
		usedKeys = { 10, 0, 1, 3, 5, 6, 8 };
		signatures = { -1, 0, -1, -1, 0, -1, -1 };
		m_isSharp = false;
		signatureCount = 5;
		break;
	case Piannect::KeyType::B_m:
		usedKeys = { 11, 1, 2, 4, 6, 7, 9 };
		signatures = { 0, 1, 0, 0, 1, 0, 0 };
		m_isSharp = true;
		signatureCount = 2;
		break;
	default:
		throw "エッ";
		break;
	}

	m_higherKeySignatures = m_isSharp ?
		std::vector<int>{ 77, 72, 79, 74, 69, 76, 71 } :
		std::vector<int>{ 71, 76, 69, 74, 67, 72, 65 };
	m_lowerKeySignatures = m_isSharp ?
		std::vector<int>{ 53, 48, 55, 50, 45, 52, 47 } :
		std::vector<int>{ 47, 52, 45, 50, 43, 48, 41 };
	while (m_higherKeySignatures.size() > signatureCount)
		m_higherKeySignatures.pop_back();
	while (m_lowerKeySignatures.size() > signatureCount)
		m_lowerKeySignatures.pop_back();
	for (int i = 0; i < 12; i++) m_isUsedKey[i] = false;
	for (int i = 0; i < 12; i++) m_noteAsPosition[i] = -1;
	for (int i = 0; i < 7; i++) {
		m_isUsedKey[usedKeys[i]] = true;
		m_noteAsPosition[usedKeys[i]] = usedKeys[i] - signatures[i];
	}
}

int KeyType::noteAsPosition(int noteNumber) const {
	return (noteNumber/12)*12 + m_noteAsPosition[noteNumber % 12];
}

bool KeyType::isUsedKey(int noteNumber) const {
	return m_isUsedKey[noteNumber % 12];
}

const std::vector<int>& KeyType::higherKeySignatures() const {
	return m_higherKeySignatures;
}

const std::vector<int>& KeyType::lowerKeySignatures() const {
	return m_lowerKeySignatures;
}

bool KeyType::isSharp() const {
	return m_isSharp;
}


}