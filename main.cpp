#define _CRT_SECURE_NO_WARNINGS

#include "Vector2.h"
#include "Window.h"
#include "Mouse.h"



int main()
{
	Graphics::get()->Create(Vector2{800, 600});

	MoveWindow(GetConsoleWindow(), 0, 0, 700, 600, true);
	SetWindowPos(Graphics::get()->getHWND(), HWND_TOP, 710, 0, 0, 0, SWP_NOSIZE);

	WindowContainer null({ 0,0 }, { 0,0 }, "", NULL);

	auto desktop = new WindowContainer({ 10,10 }, { 780, 580 }, "DT", Graphics::get()->colorRGB(165, 165, 200));

	setDesktopWindow(desktop);

	auto wind1 = new CloseButton(Graphics::get()->colorRGB(200, 200 ,200));
	auto title1 = new WindowTitle("title1", Graphics::get()->colorRGB(200, 200, 200));
	auto client1 = new WindowClient("cl1", Graphics::get()->colorRGB(230, 190, 120));
	auto box1 = new WindowBox({ 150,50 }, { 200, 300 }, "box1", title1, client1);

	auto title2 = new WindowTitle("title2", Graphics::get()->colorRGB(200, 200, 200));
	auto client2 = new WindowClient("cl2", Graphics::get()->colorRGB(230, 190, 120));
	auto boxt2 = new WindowMsgBox({ 250,150 }, { 300, 270 }, "box2", title2, client2, 1);
	auto wind2 = new CloseButton(Graphics::get()->colorRGB(200, 200, 200));
	
	auto wind3 = new OverlayWindow({ 100, 100 }, { 100, 100 }, "wind3", Graphics::get()->colorRGB(190, 60, 200));

	desktop->put(box1);
	title1->put(wind1, 1);

	desktop->put(boxt2);
	title2->put(wind2, 0);
	
	desktop->put(wind3);

	int i = 0;
	while (true)
	{
		i++;
		desktop->on_del();
		Graphics::get()->begin();
		desktop->on_draw();
		Graphics::get()->end();
		Graphics::get()->setCursorPosition({ 0,0 });
		CMouse::update();
		CMouse mouse(CMouse(), desktop->abscoord_);
		desktop->on_mouse(mouse);
		boxt2->set_name(i%10>5 ? "one" : "three");
	
		Graphics::get()->sleep(30);
	}
	return 0;
}
