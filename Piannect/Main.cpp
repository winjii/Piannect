#include "StaffNotation.h"
#include "KeyboardView.h"
#include "NoteView.h"
#include "SimpleGame.h"

namespace Piannect {


void Run() {
	Window::Resize(1760, 990);
	using namespace Piannect;
	int n = MIDIIn_GetDeviceNum();
	if (n == 0) throw "MIDIデバイスが接続されていない";
	wchar_t name[100];
	MIDIIn_GetDeviceName(0, name, 100);
	MIDIIn* midiIn = MIDIIn_Open(name);
	KeyType::Type keyType = (KeyType::Type)Random(KeyType::TypeCount - 1);
	SimpleGame sg(0, 0, Window::Width(), Window::Height()*0.7, SP<KeyType>(new KeyType(keyType)), false, false, false);
	KeyboardView kv(0, Window::Height()*0.7, Window::Width(), Window::Height()*0.3);
	while (System::Update()) {
		while (true) {
			unsigned char m[256];
			int lLen = MIDIIn_GetMIDIMessage(midiIn, m, 256);
			if (lLen == 0) break;
			if ((m[0] >> 4) == 9 && m[2] > 0) {
				int key = m[1];
				sg.push(key);
				kv.turnOn(key);
			}
			if (((m[0] >> 4) == 9 && m[2] == 0) || (m[0] >> 4) == 8) {
				int key = m[1];
				kv.turnOff(key);
			}
		}
		sg.update();
		kv.update();
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

void SimpleGameTest() {
	/*
	SimpleGame sg(0, 0, Window::Width(), Window::Height());
	while (System::Update()) {
		sg.update();
	}
	*/
}


}

void Main()
{
	enum RunMode {
		Run,
		MidiioTest,
		KeyboardViewTest,
		SimpleGameTest
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
	case SimpleGameTest:
		Piannect::SimpleGameTest();
	default:
		break;
	}
}
