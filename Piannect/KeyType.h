#pragma once


namespace Piannect {


class KeyType {
public:

	enum Type {
		None,

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

	std::array<int, 12> m_noteAsPosition;

	std::array<bool, 12> m_isUsedKey;

	std::vector<int> m_higherKeySignatures, m_lowerKeySignatures;

	bool m_isSharp;

public:

	static KeyType RandomKey();

	KeyType(Type type = Type::None);

	//Type==None�Ȃ���noteNumber�����̂܂ܕԂ�
	//���Ɋ܂܂�Ȃ�note number�Ȃ�-1��Ԃ�
	//���Ɋ܂܂��Ȃ�A�����̂悤�ɕ\���ł���͂��Ȃ̂ł��̔����Ƃ��Ă�note number��Ԃ�
	int noteAsPosition(int noteNumber) const;

	//Type==None�Ȃ���true
	//���Ɋ܂܂��note number���ǂ������肷��
	bool isUsedKey(int noteNumber) const;

	//�g���L�����̒�����note number�ŕԂ�
	//���ɏ������ׂ��������珇�Ɋi�[�����
	const std::vector<int>& higherKeySignatures() const;

	//�w���L�����̒�����note number�ŕԂ�
	//���ɏ������ׂ��������珇�Ɋi�[�����
	const std::vector<int>& lowerKeySignatures() const;

	bool isSharp() const;
};


}