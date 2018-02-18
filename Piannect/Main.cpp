#include "StaffNotation.h"

namespace Piannect {


void Run() {
	using namespace Piannect;
	int n = MIDIIn_GetDeviceNum();
	if (n == 0) throw "MIDIデバイスが接続されていない";
	wchar_t name[100];
	MIDIIn_GetDeviceName(0, name, 100);
	MIDIIn* midiIn = MIDIIn_Open(name);
	StaffNotation sn(0, 0, Window::Width(), Window::Height());
	while (System::Update()) {
		while (true) {
			unsigned char m[256];
			int lLen = MIDIIn_GetMIDIMessage(midiIn, m, 256);
			if (lLen == 0) break;
			if ((m[0] >> 4) == 9 && m[2] > 0) {
				int key = m[1];
				sn.pushNote(key);
			}
		}
		sn.update();
	}
}

void MidiioTest() {
	Console.open();
	int n = MIDIIn_GetDeviceNum();
	for (int i = 0; i < n; i++) {
		wchar_t name[100];
		MIDIIn_GetDeviceName(i, name, 100);
		printf("%ls\n", name);
	}
}


}

void Main()
{
	enum RunMode {
		Run,
		MidiioTest
	} runMode = RunMode::Run;


	Graphics2D::SetSamplerState(SamplerState::ClampLinear);
	Graphics::SetBackground(Palette::White);

	switch (runMode) {
	case Run:
		Piannect::Run();
		break;
	case MidiioTest:
		Piannect::MidiioTest();
		break;
	default:
		break;
	}
}
