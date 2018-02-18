#include "StaffNotation.h"

namespace Piannect {


void Run() {
	using namespace Piannect;
	StaffNotation sn(0, 0, Window::Width(), Window::Height());
	while (System::Update()) {
		if (KeySpace.down()) {
			sn.pushNote(60);
			sn.pushNote(72);
			sn.pushNote(73);
			sn.pushNote(48);
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
	} runMode = RunMode::MidiioTest;


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
