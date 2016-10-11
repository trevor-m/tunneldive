#pragma once

#include <windows.h>
#include <string>

#define WIDTH 1024
#define HEIGHT 768

class GameWindow
{
private:
	HWND hwnd;
	HDC hdc;
	MSG msg;
	int width, height;
public:
	GameWindow();
	~GameWindow();
	
	bool createWindow(std::string title, std::string classname, HINSTANCE hInstance, WNDPROC WndProc);//creates a window
	bool messagePump();//checks for messages
	bool destroyWindow();//destroys the window
	
	HWND getHwnd();//returns the HWND of the window
	HDC getHdc();//returns the HDC of the window

	int getWidth();
	int getHeight();
};
