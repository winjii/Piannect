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

	//�o�b�t�@�Ɏc���Ă�����͂���ɂ��A�e���͂ɂ����Ċe�C�x���g�n���h�����Ăяo��
	//�i�e�������ʂɌĂ΂�Ă��v�Z�ʂ͑����Ȃ��j
	void update();

	void addHandler(SP<ITurnOnHandler> handler);

	void addHandler(SP<ITurnOffHandler> handler);
};


}