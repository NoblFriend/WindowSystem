#define _CRT_SECURE_NO_WARNINGS
#include "C:\Users\alexe\Desktop\TX\TXLib.h"
#include "Graphics.h"
#include <ctime>

time_t StartTime = time(NULL); 

Graphics* Graphics::Graphics__ = NULL;


Graphics::Graphics ()
{}

Graphics * Graphics::get()
{
	return Graphics__;
}

void Graphics::Create(Vector2 p)
{
	static Graphics graphics;
	Graphics__ = &graphics;
	_txConsoleMode = SW_SHOW;
	txCreateWindow ( p.x_, p.y_, true );
	//printf("p = {%lg, %lg} !\n", p.x_, p.y_);
	txTextCursor(false);
    txDisableAutoPause();

    txBegin();
//  _txCanvas_RefreshLock = 100500;
}

void Graphics::begin()
{
//	txBegin ();
}

void Graphics::end()
{
//  record();

//	txEnd ();

		/*static int n = 0;
		char name[70] = "";
		time (&StartTime);
		struct tm * timeinfo = localtime (&StartTime);
		strftime(name, sizeof(name), "bmp\\Screen_%F_%H-%M-%S_", timeinfo);
		char fname[sizeof(name)] = "";
		sprintf_s(fname, "%s%05d.bmp", name, n++);
		printf("(%s)\n", fname);
		txSaveImage(fname)asserted;*/
}

void Graphics::clear()
{
	COLORREF c = txGetFillColor();
	txSetFillColor(TX_BLACK);
	txClear();
	txSetFillColor(c);
}

void Graphics::record()
{
	static int frame = 0;
	static bool state = GetKeyState(VK_CAPITAL) & 1;
	static bool pState = 0;
	static char date[150] = "";
	static char folder[150] = "";
	state = GetKeyState(VK_CAPITAL) & 1;
	if (state != pState)
	{
		if (state == 1)
		{
			char sys[150] = "";
			time (&StartTime);
			struct tm * timeinfo = localtime (&StartTime);
			strftime(date, sizeof(date), "%y_%m_%d_%H_%M_%S", timeinfo);
			sprintf(folder, "video\\%s", date);
			/*char cwd[300] = "";
			_getcwd(cwd, sizeof(cwd));
			printf("|mkdir| \t\t%s|%s\n", cwd, folder);*/
			(void) _mkdir("video");
			(void) _mkdir(folder);
		}
		if (state == 0)
		{
			char sys[350] = "";
			char ffmpeg[150] = "";
			sprintf(sys, "@start/min \"Converting...\" \"cmd /c bin\\ffmpeg -framerate 24 -i %s\\%%05d.bmp %s.avi & rmdir /s /q %s \"", folder, folder, folder);
			/*char cwd[300] = "";
			_getcwd(cwd, sizeof(cwd));
			printf("|folder| \t\t%s|%s\n", cwd, folder);*/
			//printf("|ffmpeg & rmdir| \t%s|%s\n", cwd, sys);
			system(sys);
		}
	}
	pState = state;
	if (state == 1)
	{
		char name[150] = "";
		sprintf(name, "%s\\%05d.bmp", folder, frame++);
		/*char cwd[300] = "";
		_getcwd(cwd, sizeof(cwd));
		printf("|txSaveImage| \t\t%s|%s\n",cwd,name);*/
		txSaveImage(name)asserted;
		if (frame % 30 >= 15)
		{
			drawPoint({ 10.0, txGetExtentY() - 10.0 }, 8, colorRGB(255, 60, 60));
		}
		Graphics::get()->drawText ({ 18, txGetExtentY() - 17.0 }, "Recroding...", { 8, 17 }, Graphics::get()->colorRGB(255, 255, 255), 0);
	}
}

double Graphics::sleep(int t)
{
	return txSleep(t);
}

double Graphics::getFPS()
{
	return txGetFPS();
}

HDC Graphics::getDC()
{
	return txDC();
}

HWND Graphics::getHWND()
{
	return txWindow();
}

void Graphics::drawVector (Vector2 v, Vector2 origin, double thickness, COLORREF color)
{
	Graphics::get()->drawLine(origin, v + origin, thickness, color);
	Graphics::get()->drawPoint(v + origin, 5*thickness, color);
}

void Graphics::drawPoint(Vector2 p, double thickness, COLORREF color)
{
	txSetColor (color, thickness);
	txCircle (p.x_, txGetExtentY() - p.y_, 1);
}

void Graphics::drawEllipse(Vector2 p, Vector2 r, double thickness, COLORREF fill_color, COLORREF frame_color)
{
	txSetFillColor(fill_color);
	txSetColor (frame_color, thickness);
	txEllipse(p.x_ - r.x_, txGetExtentY() - (p.y_ - r.y_), p.x_ + r.x_, txGetExtentY() - (p.y_ + r.y_));
}

void DrawLine (double x1, double y1, double x2, double y2)
{
	txSetColor (TX_WHITE, 4);
	std::cout << " p1.x_ = " << x1;
	std::cout << " p1.y_ = " << y1;
	std::cout << " p2.x_ = " << x2;
	std::cout << " p2.y_ = " << y2 << '\n';
	txLine (x1, y1, x2, y2);
	txCircle (x1, y1, 10);
	txCircle (x2, y2, 10);
}

void Graphics::drawLine(Vector2 p1, Vector2 p2, double thickness, COLORREF color)
{

	txSetColor (color, thickness);

	txLine (p1.x_, txGetExtentY() - p1.y_, p2.x_, txGetExtentY() - p2.y_);
}

void Graphics::drawRectangle(Vector2 p1, Vector2 p2, double thickness, COLORREF fill_color, COLORREF frame_color)
{
	txSetFillColor(fill_color);
	txSetColor (frame_color, thickness);
	int a = txGetExtentY();
	txRectangle(p1.x_, a-p1.y_, p2.x_, a-p2.y_);
}

void Graphics::drawText(Vector2 v1, Vector2 v2, std::string text, Vector2 size, COLORREF color, bool center /*=1*/)
{
	txSetColor (color);
	txSetTextAlign();
	txSelectFont("lucida console", size.y_, size.x_);
	unsigned temp = DT_VCENTER | DT_WORDBREAK | DT_WORD_ELLIPSIS;
	if (center) temp |= DT_CENTER;
	txDrawText(v1.x_, txGetExtentY() - v2.y_, v2.x_, txGetExtentY() - v1.y_, text.c_str(), temp);
}

void Graphics::drawText(Vector2 v1, std::string text, Vector2 size, COLORREF color, bool center /*=1*/)
{
	txSetColor (color);
	txSetTextAlign();
	txSelectFont("lucida console", size.y_, size.x_);
	if (!center) txSetTextAlign(TA_LEFT | TA_BOTTOM);
	txTextOut(v1.x_, txGetExtentY() - v1.y_, text.c_str());
}

void Graphics::drawRectText(Vector2 v, Vector2 vsize, std::string text, Vector2 tsize, COLORREF color)
{
	txSetColor (color);
	txSelectFont("lucida console", tsize.y_, tsize.x_);
	txDrawText(v.x_, txGetExtentY() - (v + vsize).y_, (v + vsize).x_, txGetExtentY() - v.y_, text.c_str());
}

void Graphics::cls()
{
	txClearConsole();

}
 
void Graphics::setCursorPosition(Vector2 coord)
{
 	txSetConsoleCursorPos(coord.x_, coord.y_);
}
 
HDC Graphics::createDC(Vector2 size)
{
    return txCreateDIBSection (size.x_, size.y_);
}

void Graphics::deleteDC(HDC dc)
{
    txDeleteDC(dc);
}

void Graphics::bitBlt(HDC dest, Vector2 coord, Vector2 size, HDC source, Vector2 piccoord)
{
    txBitBlt(dest, coord.x_, txGetExtentY() - coord.y_ - size.y_, size.x_, size.y_, source, piccoord.x_, piccoord.y_);
}

void Graphics::alphaBlend(HDC dest, Vector2 coord, Vector2 size, HDC source, Vector2 piccoord, double alpha)
{
	printf("%p, {%lg, %lg}, {%lg, %lg}, %p, {%lg, %lg}, %lg\n", dest, coord.x_, txGetExtentY() - coord.y_ - size.y_, size.x_, size.y_, source, piccoord.x_, piccoord.y_, alpha);
   	txAlphaBlend                                               (dest, coord.x_, txGetExtentY() - coord.y_ - size.y_, size.x_, size.y_, source, piccoord.x_, piccoord.y_, alpha);
}

COLORREF Graphics::setBrightness (COLORREF color, double brightness)
{
	if (brightness < 0) brightness = -brightness;

	int r = (int) (txExtractColor(color, TX_RED)   * brightness);
	int g = (int) (txExtractColor(color, TX_GREEN) * brightness);
	int b = (int) (txExtractColor(color, TX_BLUE)  * brightness);

	return RGB((r > 255 ? 255 : r), (g > 255 ? 255 : g), (b > 255 ? 255 : b));
}

COLORREF Graphics::colorRGB(double r, double g, double b)
{
	return RGB(r, g, b);
}

COLORREF Graphics::colorInverse(COLORREF color)
{
	return RGB(255 - txExtractColor(color, TX_RED), 255 - txExtractColor(color, TX_GREEN), 255 - txExtractColor(color, TX_BLUE));
}


Graphics::~Graphics()
{

}



