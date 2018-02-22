#include "StaffNotation.h"
#include "KeyboardView.h"
#include "NoteView.h"

namespace Piannect {


void Run() {
	Window::Resize(1760, 990);
	using namespace Piannect;
	int n = MIDIIn_GetDeviceNum();
	if (n == 0) throw "MIDIデバイスが接続されていない";
	wchar_t name[100];
	MIDIIn_GetDeviceName(0, name, 100);
	MIDIIn* midiIn = MIDIIn_Open(name);
	NoteView nv(0, 0, Window::Width(), Window::Height());
	while (System::Update()) {
		while (true) {
			unsigned char m[256];
			int lLen = MIDIIn_GetMIDIMessage(midiIn, m, 256);
			if (lLen == 0) break;
			if ((m[0] >> 4) == 9 && m[2] > 0) {
				int key = m[1];
				nv.pushNote(key);
			}
		}
		nv.update();
	}
	MIDIIn_Close(midiIn);
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

void KeyboardViewTest() {
	KeyboardView kv(0, 0, Window::Width(), Window::Height());
	while (System::Update()) {
		kv.update();
	}
}


}

void Main()
{
	enum RunMode {
		Run,
		MidiioTest,
		KeyboardViewTest
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
	case KeyboardViewTest:
		Piannect::KeyboardViewTest();
	default:
		break;
	}
}
