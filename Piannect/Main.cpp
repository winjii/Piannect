#include "StaffNotation.h"

void Main()
{
	Graphics2D::SetSamplerState(SamplerState::ClampLinear);
	Graphics::SetBackground(Palette::White);
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
