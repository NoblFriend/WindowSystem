#pragma once
#include "C:\Users\alexe\Documents\GitHub\SolarSystem\Vector2.h"
#include "C:\Users\alexe\Documents\GitHub\SolarSystem\Graphics.h"

class CMouse
{
private:
	Vector2 coord_;
	unsigned buttons_;

	static CMouse Cur__;
	static CMouse Old__;

	static Vector2 getCoord_();
	static unsigned getButtons_();


public:
	enum { M_LEFTUP = 1, M_LEFTDOWN = 2, M_RIGHTUP = 4, M_RIGHTDOWN = 8, M_LEFTDRAG = 16, M_RIGHTDRAG = 32, M_FREEDRAG = 64 , M_CONSIDERED};

	static unsigned msg_;
	CMouse();
	CMouse(const CMouse &mouse, const Vector2 &origin);

	static unsigned getButtons();
	static Vector2  getCoord();
	static Vector2 getDeltaCoord();
	static void update();
};

