#include "Window.h"
#include <conio.h>

static WindowContainer* DesktopWindow;

void setDesktopWindow(WindowContainer* wnd)
{
	DesktopWindow = wnd;
}
WindowContainer* getDesktopWindow()
{
	return DesktopWindow;
}

Window::Window(Vector2 coord, Vector2 size, const char* name, COLORREF color)
	:	coord_(coord),
		size_(size),
		name_(name),
		color_(color),
		is_active(1),
		parrentWind(NULL)
{}

void Window::on_draw()
{
	if (is_active == false) return;
	if (parrentWind == nullptr)
	{
		abscoord_ = coord_;
	}
	else
	{
		abscoord_ = coord_ + parrentWind->abscoord_;
	}
	Graphics::get()->drawRectangle(abscoord_, abscoord_ + size_, 1, color_, Graphics::get()->colorRGB(255, 255, 255));
	//Graphics::get()->drawText({ coord_.x_ + size_.x_*0.5, coord_.y_ + size_.y_- 10}, name_, { 8,16 }, Graphics::get()->colorInverse(color_));
}

void Window::on_mouse(CMouse mouse)
{
	
}

bool Window::on_active()
{
	return true;
}

void Window::close()
{
	if (parrentWind != NULL)
	{
		parrentWind->remove(this);
	}
}


WindowContainer::WindowContainer(Vector2 coord, Vector2 size, const char* name, COLORREF color)
	: Window(coord, size, name, color),
	inactiveWind(NULL)
{}

void WindowContainer::put(Window* wind)
{
	wind->parrentWind = this;
	subwindows.push_back(wind);
}

void WindowContainer::remove(Window* wind)
{
	for (size_t i = 0; i < subwindows.size(); i++)
	{
		if (subwindows[i] == wind)
		{
			wind->is_active = 0;
			//printf("active %d of %s\n", subwindows[i]->is_active, subwindows[i]->name_);
			WindowContainer* wcptr = dynamic_cast<WindowContainer*> (wind);
			if (wcptr) wcptr->remove();
			break;
		}
	}
}

void WindowContainer::remove()
{
	for (size_t i = 0; i < subwindows.size(); i++)
	{
		subwindows[i]->is_active = 0;
		//printf("active %d of %s\n", subwindows[i]->is_active, subwindows[i]->name_);
		WindowContainer* wcptr = dynamic_cast<WindowContainer*> (subwindows[i]);
		if (wcptr) wcptr->remove();
	}
}

void WindowContainer::tree()
{
	for (size_t i = 0; i < subwindows.size(); i++)
	{
		WindowContainer* winptr = dynamic_cast<WindowContainer*> (subwindows[i]);
		if (!winptr) printf("\t");
		printf("name_ = %s, is_active = %d\t\t\t\t\t\n", subwindows[i]->name_, subwindows[i]->is_active);
		if (winptr)
		{
			printf("\t");
			winptr->tree();
		}
	}
}

void WindowContainer::on_del()
{
	for (size_t from = 0; from < subwindows.size(); from++)
	{
		WindowContainer* wcptr = dynamic_cast<WindowContainer*> (subwindows[from]);
		if (wcptr)
		{
			wcptr->on_del();
		}
		if (subwindows[from]->is_active == false)
		{
			Window* temp = subwindows[from];
			delete temp;
			subwindows.erase(subwindows.begin() + from--);
		}
	}
}			



void WindowContainer::on_draw()
{
	Window::on_draw();
	for (size_t i = 0; i < subwindows.size(); i++)
	{
		if (subwindows[i]->is_active == false) continue;
		printf("Drow %s\t\t\n", subwindows[i]->name_);
		subwindows[i]->on_draw();
		//Graphics::get()->sleep(1);
		//_getch();
	}
}

void WindowContainer::on_mouse(CMouse mouse)
{
	

	/*printf("From %s {%lg, %lg} wnd = %s\n", __FUNCTION__, coord.x_, coord.y_, name_);
	printf("From %s {%lg, %lg}\n", __FUNCTION__, CMouse::getCoord().x_, CMouse::getCoord().y_);*/

	for (int i = subwindows.size() - 1; i >= 0; i--)
	{
		if (subwindows[i]->is_active == false) continue;
		/*printf("checking wnd[%d] = %s, with rect from {%lg, %lg} to {%lg, %lg}\n", i, subwindows[i]->name_,
				subwindows[i]->coord_.x_,
				subwindows[i]->coord_.y_,
				(subwindows[i]->coord_ + subwindows[i]->size_).x_,
				(subwindows[i]->coord_ + subwindows[i]->size_).y_);*/
		if (mouse.getCoord().isIn({ subwindows[i]->abscoord_, subwindows[i]->abscoord_ + subwindows[i]->size_ }))
		{
			/*printf("\"Hey, i'm here\", from line %d of %s says, wnd = %s\n", __LINE__, __FILE__, subwindows[i]->name_);
			*/
			subwindows[i]->on_mouse(CMouse(mouse, subwindows[i]->coord_));
			if (CMouse::msg_ & (CMouse::M_LEFTDOWN | CMouse::M_RIGHTDOWN))
			{
				if (subwindows[i]->on_active())std::swap(subwindows[i], subwindows.back());
			}
			break;
		}
	}
	/*printf("\n");
	*/
}

bool WindowContainer::on_active()
{
	return true;
}


WindowTitle::WindowTitle(const char* name, COLORREF color)
	:	WindowContainer({ -1, -1 }, { -1, -1 }, name, color),
		rcount_(0),
		lcount_(0),
		is_dragging_(0)
{}

void WindowTitle::put(Window* wind, bool to_left)
{
	wind->coord_.y_ = size_.y_*0.1;
	wind->size_ = {size_.y_*0.8, size_.y_*0.8};
	if (to_left)
	{
		wind->coord_.x_ = lcount_*size_.y_ + size_.y_*0.1;
		lcount_++;
	}
	else
	{
		wind->coord_.x_ = -(rcount_+1)*size_.y_ + size_.y_*0.1 + size_.x_;
		rcount_++;
	}
	WindowContainer::put(wind);
}

void WindowTitle::on_draw()
{
	WindowContainer::on_draw();
	Graphics::get()->drawText(abscoord_ - coord_ + Vector2{ coord_.x_ + lcount_ * size_.y_, coord_.y_ },
							  abscoord_ - coord_ + Vector2{ coord_.x_ + size_.x_ - rcount_ * size_.y_, coord_.y_ + size_.y_ }, 
							  name_, { 7, 16 }, NULL);
}

void WindowTitle::on_mouse(CMouse mouse)
{
	WindowContainer::on_mouse(mouse);
	if ((is_dragging_ == false) && (CMouse::msg_ & CMouse::M_LEFTDOWN) && !(CMouse::msg_ & CMouse::M_CONSIDERED)) is_dragging_ = true;
}

bool WindowTitle::on_active()
{
	return false;
}

WindowClient::WindowClient(const char* name, COLORREF color)
	:	WindowContainer({ -1, -1 }, { -1, -1 }, name, color)
{}

void WindowClient::put(Window* wind)
{
	WindowContainer::put(wind);
}

void WindowClient::on_draw()
{
	WindowContainer::on_draw();
}

bool WindowClient::on_active()
{
	return false;
}

WindowBox::WindowBox(Vector2 coord, Vector2 size, const char* name, WindowTitle* title, WindowClient* client)
	:	WindowContainer(coord, size, name, NULL)

{
	title->size_ = { size_.x_, 35 };
	title->coord_ = { 0, size_.y_ - 35 };
	wtitle_ = title;
	WindowContainer::put(title);

	client->size_ = size_ + Vector2{ 0, -35 };
	client->coord_ = { 0, 0 };
	wclient_ = client;
	WindowContainer::put(client);
}

void WindowBox::on_draw()
{
	if (wtitle_->is_dragging_ == true)
		coord_ = coord_ + CMouse::getDeltaCoord();
	if (wtitle_->is_dragging_ == true && !(CMouse::getButtons() & 1))
		wtitle_->is_dragging_ = false;
	WindowContainer::on_draw();
}

WindowMsgBox::WindowMsgBox(Vector2 coord, Vector2 size, const char* name, WindowTitle* title, WindowClient* client, int state) :
	WindowBox(coord, size, name, title, client)
{
	const Vector2 b_size = { 80, 30 };
	if (state & B_OK)
	{
		auto ok = new WindowButton({ size_.x_/2 - b_size.x_/2 , b_size.y_ }, b_size, "OK", Graphics::get()->colorRGB(255, 255, 255));
		put(ok);
	}
}


void WindowMsgBox::on_draw()
{
	WindowBox::on_draw();
	Graphics::get()->drawRectText(abscoord_ + Vector2{ 10, 10 }, size_ - Vector2{ 20, 20 }, name_, { 9, 20 }, RGB(0, 0, 0));
	
}

void WindowMsgBox::set_name(const char* name)
{
	name_ = name;
}

WindowButton::WindowButton(Vector2 coord, Vector2 size, const char* name, COLORREF color)
	:	Window(coord, size, name, color),
		pstate(false)
{}

void WindowButton::on_draw()
{
	if (pstate)
	{
		if (!CMouse::getCoord().isIn({ abscoord_, abscoord_ + size_ }) && !(CMouse::getButtons() & 1))
			pstate = false;
	}


	abscoord_ = coord_ + parrentWind->abscoord_;
	Graphics::get()->drawRectangle(abscoord_, abscoord_ + size_, 0, color_, color_);
	const int tline = 3;
	double brightness = 1.7;
	double k = 1.41;
	if (pstate)
	{
		brightness = 1 / brightness;
		k = 1 / k;
		Graphics::get()->drawRectangle(abscoord_ + Vector2{ tline, tline }, 
									   abscoord_ + size_ - Vector2{ tline, tline }, 0, 
									   Graphics::get()->setBrightness(color_, 0.8), Graphics::get()->setBrightness(color_, 0.8));
	}
	/*
	setWindowOrigin(this);
	Graphics::get()->drawLine(Vector2{ coord_.x_ + tline,  coord_.y_ + tline },
							  Vector2{ coord_.x_ + tline, (coord_ + size_).y_ - tline }, 
							  1.41 / k, Graphics::get()->setBrightness(color_, 0.9*  brightness));
	Graphics::get()->drawLine(Vector2{ coord_.x_ + tline, (coord_ + size_).y_ - tline },
							  Vector2{ (coord_ + size_).x_ - tline, (coord_ + size_).y_ - tline }, 
							  1.41 / k, Graphics::get()->setBrightness(color_, 0.9*  brightness));

	Graphics::get()->drawLine(Vector2{ coord_.x_ + tline,  coord_.y_ + tline },
							  Vector2{ (coord_ + size_).x_ - tline,  coord_.y_ + tline },
							  1.41*k, Graphics::get()->setBrightness(color_, 0.9 * 1 / brightness));
	Graphics::get()->drawLine(Vector2{ (coord_ + size_).x_ - tline,  coord_.y_ + tline },
							  Vector2{ (coord_ + size_).x_ - tline, (coord_ + size_).y_ - tline },
							  1.41*k, Graphics::get()->setBrightness(color_, 0.9 * 1 / brightness));
	*/

	Graphics::get()->drawLine(abscoord_ - coord_ + Vector2{ coord_.x_ + tline,  coord_.y_ + tline },
		abscoord_ - coord_ + Vector2{ coord_.x_ + tline, (coord_ + size_).y_ - tline }, 1.41 / k, Graphics::get()->setBrightness(color_, 0.9*  brightness));
	Graphics::get()->drawLine(abscoord_ - coord_ + Vector2{ coord_.x_ + tline, (coord_ + size_).y_ - tline },
		abscoord_ - coord_ + Vector2{ (coord_ + size_).x_ - tline, (coord_ + size_).y_ - tline }, 1.41 / k, Graphics::get()->setBrightness(color_, 0.9*  brightness));

	Graphics::get()->drawLine(abscoord_ - coord_ + Vector2{ coord_.x_ + tline,  coord_.y_ + tline },
		abscoord_ - coord_ + Vector2{ (coord_ + size_).x_ - tline,  coord_.y_ + tline }, 1.41*k, Graphics::get()->setBrightness(color_, 0.9 * 1 / brightness));
	Graphics::get()->drawLine(abscoord_ - coord_ + Vector2{ (coord_ + size_).x_ - tline,  coord_.y_ + tline },
		abscoord_ - coord_ + Vector2{ (coord_ + size_).x_ - tline, (coord_ + size_).y_ - tline }, 1.41*k, Graphics::get()->setBrightness(color_, 0.9 * 1 / brightness));

		if (pstate)
		{
			Graphics::get()->drawText(abscoord_ - Vector2{ -tline, tline } *0.2,
									  abscoord_ + size_ - Vector2{ -tline, tline } *0.2, name_, { 7, 15 }, Graphics::get()->colorRGB(0, 0, 0));
		}
		else
		{
			Graphics::get()->drawText(abscoord_ + Vector2{ -tline, tline } *0.2,
									  abscoord_ + size_ + Vector2{ -tline, tline } *0.2, name_, { 7, 15 }, Graphics::get()->colorRGB(0, 0, 0));
		}
		if (strcmp(name_, "OK") == 0)
		{
			//Graphics::get()->drawEllipse(abscoord_, { 10, 10 }, 2, Graphics::get()->colorRGB(255, 0, 0), Graphics::get()->colorRGB(255, 0, 0));
		}
}

void WindowButton::on_mouse(CMouse mouse)
{
	if (!pstate)
	{
		if (CMouse::msg_ & CMouse::M_LEFTDOWN)
		{
			CMouse::msg_ |= CMouse::M_CONSIDERED;
			pstate = true;
		}
	}
	else if (pstate)
	{
		if (CMouse::msg_ & CMouse::M_LEFTUP)
		{
			CMouse::msg_ |= CMouse::M_CONSIDERED;
			on_action();
			pstate = false;
		}
	}
}

void WindowButton::on_action()
{

}


CloseButton::CloseButton (COLORREF color)
	:	WindowButton({ -1, -1 }, { -1,-1 }, "X", color)
{}

void CloseButton::on_action()
{
	parrentWind->parrentWind->close();
}


OverlayWindow::OverlayWindow(Vector2 coord, Vector2 size, const char* name, COLORREF color)
	:	Window(coord, size, name, color)
{


}

void OverlayWindow::on_draw()
{
	WindowContainer* desktop = getDesktopWindow();
	static HDC dc = Graphics::get()->createDC(desktop->size_);
	Graphics::get()->alphaBlend(Graphics::get()->getDC(), desktop->abscoord_, desktop->size_, dc, { 0,0 }, 0.5);
	printf("desktop->coord_ = {%lg, %lg}\n", desktop->coord_.x_, desktop->coord_.y_);
	Graphics::get()->sleep(1000);
	printf("good morning\n");
	//Graphics::get()->drawRectangle(desktop->abscoord_, desktop->abscoord_ + desktop->size_, 1, Graphics::get()->colorRGB(255, 0, 0), Graphics::get()->colorRGB(255, 0, 0));
	Window::on_draw();
}

void OverlayWindow::on_mouse(CMouse mouse)
{

}

bool OverlayWindow::on_active()
{
	return Window::on_active();
}

