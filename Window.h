#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Vector2.h"
#include "Mouse.h"

struct WindowContainer;

void setDesktopWindow(WindowContainer* wnd);
WindowContainer* getDesktopWindow();

struct Window
{
	Vector2 coord_;
	Vector2 size_;
	const char* name_;
	COLORREF color_;

	WindowContainer* parrentWind;

	bool is_active;

	Vector2 abscoord_;

	Window(Vector2 coord, Vector2 size, const char* name, COLORREF color);


	virtual void on_draw() = 0;
	virtual void on_mouse(CMouse mouse);
	virtual bool on_active();
	void close();
};

struct WindowContainer : Window
{
	std::vector<Window*> subwindows;

	Window* inactiveWind;

	WindowContainer(Vector2 coord, Vector2 size, const char* name, COLORREF color);
	void put(Window* wind);
	void remove(Window* wind);
	void remove();
	void tree();
	virtual void on_del();
	virtual void on_draw()   override;
	virtual void on_mouse(CMouse mouse)  override;
	virtual bool on_active() override;
};		
		
		
//TODO MSGBOX
		
//farfuture floatingmsgbox
		
	struct WindowTitle : WindowContainer
	{	
		int rcount_;
		int lcount_;

		bool is_dragging_;

		WindowTitle(const char* name, COLORREF color);

		void put(Window* wind, bool to_left);
		virtual void on_draw()  override;
		virtual void on_mouse(CMouse mouse) override;
		virtual bool on_active() override;
	};	
		
	struct WindowClient : WindowContainer
	{	
		WindowClient(const char* name, COLORREF color);

		void put(Window* wind);
		virtual void on_draw()  override;
		virtual bool on_active() override;
	};	
		
		
		
	struct WindowBox : WindowContainer
	{	
		WindowTitle*  wtitle_;
		WindowClient* wclient_;

		WindowBox(Vector2 coord, Vector2 size, const char* name, WindowTitle* title, WindowClient* client);

		void on_draw() override;
		
	};	
		
	struct WindowMsgBox : WindowBox
	{	
		enum { B_OK = 1, N_CANCEL = 2, B_REPEAT = 4, B_YES = 8, B_NO = 16 };

		WindowMsgBox(Vector2 coord, Vector2 size, const char* name, WindowTitle* title, WindowClient* client, int state);

		void set_name(const char* name);

		virtual void on_draw() override;
	};	
		
		
		
struct WindowButton : Window
{
	bool pstate;
	bool c = false;

	WindowButton(Vector2 coord, Vector2 size, const char* name, COLORREF color);

	virtual void on_draw() override;
	virtual void on_mouse(CMouse mouse);

	virtual void on_action();
};
		
	struct CloseButton : WindowButton
	{
		CloseButton(COLORREF color);

		virtual void on_action() override;
	};
		

struct OverlayWindow : Window
{
	OverlayWindow(Vector2 coord, Vector2 size, const char* name, COLORREF color);

	virtual void on_draw() override;
	virtual void on_mouse(CMouse mouse) override;
	virtual bool on_active() override;
};
		
		