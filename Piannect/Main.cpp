#include "StaffNotation.h"
#include "KeyboardView.h"
#include "NoteView.h"
#include "BlindQuiz.h"

namespace Piannect {


void Run() {
	Window::Resize(1760, 990);
	using namespace Piannect;
	int n = MIDIIn_GetDeviceNum();
	if (n == 0) throw "MIDIデバイスが接続されていない";
	wchar_t name[100];
	MIDIIn_GetDeviceName(0, name, 100);
	MIDIIn* midiIn = MIDIIn_Open(name);
	BlindQuiz bq(0, 0, Window::Width(), Window::Height()*0.7, KeyType::RandomKey(), 3);
	KeyboardView kv(0, Window::Height()*0.7, Window::Width(), Window::Height()*0.3);
	while (System::Update()) {
		while (true) {
			unsigned char m[256];
			int lLen = MIDIIn_GetMIDIMessage(midiIn, m, 256);
			if (lLen == 0) break;
			if ((m[0] >> 4) == 9 && m[2] > 0) {
				int note = m[1];
				bq.push(note);
				kv.turnOn(note);
			}
			if (((m[0] >> 4) == 9 && m[2] == 0) || (m[0] >> 4) == 8) {
				int note = m[1];
				kv.turnOff(note);
			}
		}
		bq.update();
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
