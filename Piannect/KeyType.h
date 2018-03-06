#pragma once


namespace Piannect {


class KeyType {
public:

	enum Type {
		Cf,
		C,
		Cs,
		Df,
		D,
		Ef,
		E,
		F,
		Fs,
		Gf,
		G,
		Af,
		A,
		Bf,
		B,

		C_m,
		Cs_m,
		D_m,
		Ds_m,
		Ef_m,
		E_m,
		F_m,
		Fs_m,
		G_m,
		Gs_m,
		Af_m,
		A_m,
		As_m,
		Bf_m,
		B_m
	};

private:

	Type m_type;

	std::array<int, 12> m_keyAsPosition;

	std::array<bool, 12> m_isUsedKey;

	std::vector<int> m_higherKeySignatures, m_lowerKeySignatures;

	bool m_isSharp;

public:

	KeyType(Type type);

	//���Ɋ܂܂��key�łȂ��ꍇ��-1��Ԃ�
	//���̉e���ŗՎ��L�����g�킸�ɔ����̂悤�ɕ\���ł���ꍇ�A���̔����Ƃ��Ă�key��Ԃ�
	//�Վ��L�����g��Ȃ��ƃ_����key�̏ꍇ�A���̂܂܍����Ƃ��Ă�key��Ԃ�
	int keyAsPosition(int key);

	//���Ɋ܂܂��key���ǂ������肷��
	bool isUsedKey(int key);

	//�g���L�����̒�����key�ŕԂ�
	//���ɏ������ׂ��������珇�Ɋi�[�����
	const std::vector<int>& higherKeySignatures();

	//�w���L�����̒�����key�ŕԂ�
	//���ɏ������ׂ��������珇�Ɋi�[�����
	const std::vector<int>& lowerKeySignatures();

	bool isSharp();
};


}