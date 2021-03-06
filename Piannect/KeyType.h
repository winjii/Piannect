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

	//Type==Noneなら常にnoteNumberをそのまま返す
	//調に含まれないnote numberなら-1を返す
	//調に含まれるなら、白鍵のように表示できるはずなのでその白鍵としてのnote numberを返す
	int noteAsPosition(int noteNumber) const;

	//Type==Noneなら常にtrue
	//調に含まれるnote numberかどうか判定する
	bool isUsedKey(int noteNumber) const;

	//ト音記号側の調合をnote numberで返す
	//左に書かれるべき調合から順に格納される
	const std::vector<int>& higherKeySignatures() const;

	//ヘ音記号側の調合をnote numberで返す
	//左に書かれるべき調合から順に格納される
	const std::vector<int>& lowerKeySignatures() const;

	bool isSharp() const;
};


}