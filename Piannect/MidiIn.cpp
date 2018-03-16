#include "stdafx.h"
#include "MidiIn.h"


namespace Piannect {




int MidiIn::DeviceNum() {
	return MIDIIn_GetDeviceNum();
}

std::wstring MidiIn::DeviceName(int index) {
	wchar_t nameW[128];
	MIDIIn_GetDeviceName(index, nameW, 128);
	return std::wstring(nameW);
}

SP<MidiIn> MidiIn::Create(const std::wstring &name) {
	MIDIIn* res = MIDIIn_Open(name.c_str());
	if (!res) throw "failed MIDIIn_Open! (invalid name?)";
	return SP<MidiIn>(new MidiIn(res));
}

MidiIn::MidiIn(MIDIIn* midiIn) : m_p(midiIn) {
}

MidiIn::~MidiIn() {
	MIDIIn_Close(m_p);
}

void MidiIn::update() {
	while (true) {
		unsigned char m[256];
		int lLen = MIDIIn_GetMIDIMessage(m_p, m, 256);
		if (lLen == 0) break;
		if ((m[0] >> 4) == 9 && m[2] > 0) {
			int note = m[1];
			for each (SP<ITurnOnHandler> h in m_turnOnHandlers) {
				h->onTurnOn(note);
			}
		}
		else if (((m[0] >> 4) == 9 && m[2] == 0) || (m[0] >> 4) == 8) {
			int note = m[1];
			for each (SP<ITurnOffHandler> h in m_turnOffHandlers) {
				h->onTunrOff(note);
			}
		}
	}
}

void MidiIn::addHandler(SP<ITurnOnHandler> handler) {
	m_turnOnHandlers.push_back(handler);
}

void MidiIn::addHandler(SP<ITurnOffHandler> handler) {
	m_turnOffHandlers.push_back(handler);
}


}