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

	Font menuFont(50);
	std::vector<String> menu = {
		U"練習1",
		U"練習2",
		U"練習3",
		U"練習4"
	};
	double width = 0;
	for each (String s in menu) {
		width = std::max(width, menuFont(s).boundingRect().w);
	}
	width += 100;
	double height = 80;
	double margin = height*0.3;

	auto drawRect = [](const RectF &r, double invRate = 0) {
		r.drawShadow(Vec2(0, 0), 20, 0, Color(150*invRate));
		r.draw(Palette::White);
	};
	auto easeRect = [](const RectF &a, const RectF &b, double t) {
		Vec2 pos(EaseOut(Easing::Quart, a.pos, b.pos, t));
		Vec2 size(EaseOut(Easing::Quart, a.size, b.size, t));
		return RectF(pos, size);
	};

	RectF selectedRect;
	Stopwatch sw;
	int selectedIndex = -1;
	while (System::Update()) {
		Window::ClientRect().draw(Palette::White);
		double baseY = (Window::Height() - (height*menu.size() + margin*menu.size() + margin))/2;
		if (sw.sF() >= 0.5) {
			sw.reset();
			break;
		}
		double t = sw.sF()/0.5;
		auto drawString = [&](int index) {
			Vec2 center(Window::Width()/2, baseY + margin*index + height*index + margin + height/2);
			DrawableText drawable = menuFont(menu[index]);
			drawable.draw(Arg::center(center), Color(Palette::Black, 255*(1 - t)));
		};
		for (int i = 0; i < (int)menu.size(); i++) {
			String s = menu[i];
			double y = baseY + margin*i + height*i + margin;
			RectF r((Window::Width() - width)/2, y, width, height);
			if (!sw.isRunning() && r.leftClicked()) {
				selectedRect = r;
				selectedIndex = i;
				sw.start();
			}
			if (selectedIndex == i) continue;
			drawRect(r, t);
			drawString(i);
		}
		if (selectedIndex != -1) {
			drawRect(easeRect(selectedRect, Window::ClientRect(), t));
			drawString(selectedIndex);
		}
	}
	if (selectedIndex == 0) {
		AbsolutePositionQuiz game(0, 0, Window::Width(), Window::Height(), midiIn, false);
		while (System::Update()) game.update();
	}
	else if (selectedIndex == 1) {
		AbsolutePositionQuiz game(0, 0, Window::Width(), Window::Height(), midiIn, true);
		while (System::Update()) game.update();
	}
	else if (selectedIndex == 2) {
		RelativePositionQuiz game(0, 0, Window::Width(), Window::Height(), midiIn);
		while (System::Update()) game.update();
	}
	else if (selectedIndex == 3) {
		int maxSize = 3;
		Font large(200), small(80);
		Line l(Window::Center() - Vec2(300, 0), Window::Center() - Vec2(300 + 100, 0));
		Line r(Window::Center() + Vec2(300, 0), Window::Center() + Vec2(300 + 100, 0));
		RectF lRect(0, 0, Window::Width()/2 - 300, Window::Height());
		RectF rRect(Window::Width()/2 + 300, 0, Window::Width()/2 - 300, Window::Height());
		while (System::Update()) {
			if (lRect.leftClicked()) {
				maxSize = std::max(2, maxSize - 1);
			}
			if (rRect.leftClicked()) {
				maxSize++;
			}
			small(U"音符数").draw(Arg::center(Window::Center() - Vec2(0, 200)), Palette::Gray);
			large(maxSize).draw(Arg::center(Window::Center()), Palette::Black);
			bool ok = small(U"OK")
				.draw(Arg::center(Window::Center() + Vec2(0, 200)), Palette::Gray).stretched(Vec2(50, 20))
				.drawFrame(1, Palette::Black)
				.leftClicked();
			l.drawArrow(1, Vec2(80, 100), Palette::Gray);
			r.drawArrow(1, Vec2(80, 100), Palette::Gray);

			if (ok) break;
		}
		BlindQuiz game(0, 0, Window::Width(), Window::Height(), KeyType::RandomKey(), maxSize, midiIn);
		while (System::Update()) game.update();
	}
	else {
		while (System::Update()) menuFont(U"エッ").draw(Vec2::Zero(), Palette::Black);
	}

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
