#pragma once

namespace Piannect {


class MidiIn {
public:


	class ITurnOnHandler {
	public:
		virtual void onTurnOn(int noteNumber) = 0;
	};

	
	class ITurnOffHandler {
	public:
		virtual void onTunrOff(int noteNumber) = 0;
	};
	

private:

	MIDIIn* m_p;

	std::list<SP<ITurnOnHandler>> m_turnOnHandlers;

	std::list<SP<ITurnOffHandler>> m_turnOffHandlers;

public:

	static int DeviceNum();

	static std::wstring DeviceName(int index);

	static SP<MidiIn> Create(const std::wstring &name);

	MidiIn(MIDIIn* midiIn);

	~MidiIn();

	//バッファに残っている入力を空にし、各入力において各イベントハンドラを呼び出す
	//（各所から大量に呼ばれても計算量は増えない）
	void update();

	void addHandler(SP<ITurnOnHandler> handler);

	void addHandler(SP<ITurnOffHandler> handler);
};


}