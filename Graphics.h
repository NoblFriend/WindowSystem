#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include "Vector2.h"




class Graphics
{
private:
	static Graphics* Graphics__;
	Vector2 origin_;
public:
	Graphics ();
	static Graphics* get();
	static void Create (Vector2 p);
	static void begin();
	static void end();
	static void clear();
	static void record();
	static double sleep(int t);
	static double getFPS ();
	//static void setOrigin();
	static HDC  getDC();		
	static HWND getHWND();	
	static void drawVector(Vector2 v, Vector2 origin, double thickness, COLORREF color);
	static void drawPoint(Vector2 p, double thickness, COLORREF color);
	static void drawEllipse (Vector2 p, Vector2 r, double thickness, COLORREF fill_color, COLORREF frame_color);
	static void drawLine(Vector2 p1, Vector2 p2, double thickness, COLORREF color);
	static void drawRectangle(Vector2 p1, Vector2 p2, double thickness, COLORREF fill_color, COLORREF frame_color);
	static void drawText(Vector2 v1, Vector2 v2, std::string text, Vector2 size, COLORREF color, bool center = 1);
	static void drawText(Vector2 v1, std::string text, Vector2 size, COLORREF color, bool center = 1);
	static void drawRectText(Vector2 v, Vector2 vsize, std::string text, Vector2 tsize, COLORREF color);
	static void cls();
	static void setCursorPosition(Vector2 coord);
	static void alphaBlend(HDC dest, Vector2 coord, Vector2 size, HDC source, Vector2 piccoord , double alpha);
	static void bitBlt(HDC dest, Vector2 coord, Vector2 size, HDC source, Vector2 piccoord);
	static HDC  createDC(Vector2 size);
	static COLORREF setBrightness (COLORREF color, double k);
	static COLORREF colorRGB (double r, double g, double b); 
	static COLORREF colorInverse(COLORREF color);
   ~Graphics ();
};
