#include "StaffNotation.h"
#include "KeyboardView.h"
#include "NoteView.h"
#include "BlindQuiz.h"
#include "MidiIn.h"
#include "AbsolutePositionQuiz.h"
#include "RelativePositionQuiz.h"

namespace Piannect {


void Run() {
	Window::Resize(1760, 990);
	using namespace Piannect;
	int n = MidiIn::DeviceNum();
	if (n == 0) throw "MIDIデバイスが接続されていない";
	SP<MidiIn> midiIn = MidiIn::Create(MidiIn::DeviceName(0));
	//BlindQuiz game(0, 0, Window::Width(), Window::Height(), KeyType::RandomKey(), 3, midiIn);
	//AbsolutePositionQuiz game(0, 0, Window::Width(), Window::Height(), midiIn, true);
	RelativePositionQuiz game(0, 0, Window::Width(), Window::Height(), KeyType::RandomKey(), midiIn);
	while (System::Update()) {
		game.update();
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
