#include "Mouse.h"

CMouse CMouse::Cur__ = CMouse();
CMouse CMouse::Old__ = CMouse();
unsigned CMouse::msg_ = 0;

CMouse::CMouse() :
	coord_(Cur__.coord_),
	buttons_(Cur__.buttons_)
{}

CMouse::CMouse(const CMouse &mouse, const Vector2 &origin) :
	coord_(mouse.coord_ - origin),
	buttons_(mouse.buttons_)
{}



Vector2 CMouse::getCoord_()
{
	POINT p = {};
	GetCursorPos(&p);
	RECT r = {};
	ScreenToClient(Graphics::get()->getHWND(), &p);
	GetClientRect(Graphics::get()->getHWND(), &r);
	return Vector2{ p.x - (double)r.left,  (double)r.bottom - p.y };
}

unsigned CMouse::getButtons_()
{
	return ((GetAsyncKeyState(MK_LBUTTON) >> 15) & 1) | (((GetAsyncKeyState(MK_RBUTTON) >> 14) & 2));
}


unsigned CMouse::getButtons()
{
	return Cur__.buttons_;
}

Vector2 CMouse::getCoord()
{
	return Cur__.coord_;
}


Vector2 CMouse::getDeltaCoord()
{
	return Cur__.coord_ - Old__.coord_;
}


void CMouse::update()
{
	Old__ = Cur__;

	Cur__.buttons_ = getButtons_();
	Cur__.coord_ = getCoord_();
	unsigned r = 0;

	if (( Cur__.buttons_ & 1      ) && ((Old__.buttons_ & 1) == 0))
		r |= M_LEFTDOWN;

	if (((Cur__.buttons_ & 1) == 0) &&  (Old__.buttons_ & 1)     )
		r |= M_LEFTUP;

	if (( Cur__.buttons_ & 2      ) && ((Old__.buttons_ & 2) == 0))
		r |= M_RIGHTDOWN;

	if (((Cur__.buttons_ & 2) == 0) &&  (Old__.buttons_ & 2)     )
		r |= M_RIGHTUP;

	if (Cur__.coord_ != Old__.coord_)
	{
		if (Cur__.buttons_ & 1)
			r |= M_LEFTDRAG;
		else if (Cur__.buttons_ & 2)
			r |= M_RIGHTDRAG;
		else
			r |= M_FREEDRAG;
	}

	Cur__.msg_ = r;
}

