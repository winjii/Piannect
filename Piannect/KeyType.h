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

	//調に含まれるkeyでない場合は-1を返す
	//調の影響で臨時記号を使わずに白鍵のように表示できる場合、その白鍵としてのkeyを返す
	//臨時記号を使わないとダメなkeyの場合、そのまま黒鍵としてのkeyを返す
	int keyAsPosition(int key);

	//調に含まれるkeyかどうか判定する
	bool isUsedKey(int key);

	//ト音記号側の調合をkeyで返す
	//左に書かれるべき調合から順に格納される
	const std::vector<int>& higherKeySignatures();

	//ヘ音記号側の調合をkeyで返す
	//左に書かれるべき調合から順に格納される
	const std::vector<int>& lowerKeySignatures();

	bool isSharp();
};


}