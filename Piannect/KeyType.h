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

	//Type==None‚È‚çí‚ÉnoteNumber‚ğ‚»‚Ì‚Ü‚Ü•Ô‚·
	//’²‚ÉŠÜ‚Ü‚ê‚È‚¢note number‚È‚ç-1‚ğ•Ô‚·
	//’²‚ÉŠÜ‚Ü‚ê‚é‚È‚çA”’Œ®‚Ì‚æ‚¤‚É•\¦‚Å‚«‚é‚Í‚¸‚È‚Ì‚Å‚»‚Ì”’Œ®‚Æ‚µ‚Ä‚Ìnote number‚ğ•Ô‚·
	int noteAsPosition(int noteNumber) const;

	//Type==None‚È‚çí‚Étrue
	//’²‚ÉŠÜ‚Ü‚ê‚énote number‚©‚Ç‚¤‚©”»’è‚·‚é
	bool isUsedKey(int noteNumber) const;

	//ƒg‰¹‹L†‘¤‚Ì’²‡‚ğnote number‚Å•Ô‚·
	//¶‚É‘‚©‚ê‚é‚×‚«’²‡‚©‚ç‡‚ÉŠi”[‚³‚ê‚é
	const std::vector<int>& higherKeySignatures() const;

	//ƒw‰¹‹L†‘¤‚Ì’²‡‚ğnote number‚Å•Ô‚·
	//¶‚É‘‚©‚ê‚é‚×‚«’²‡‚©‚ç‡‚ÉŠi”[‚³‚ê‚é
	const std::vector<int>& lowerKeySignatures() const;

	bool isSharp() const;
};


}